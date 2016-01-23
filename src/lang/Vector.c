#ifndef __LISP_LANG_VECTOR_C__
#define __LISP_LANG_VECTOR_C__


static lisp_VectorArray* lisp_VectorArray_constructor(lisp_VectorArray* array, lisp_Value** values) {
    array->ref_count = 1;
    array->values = values;
    return array;
}

static void lisp_VectorArray_destructor(lisp_State* state, lisp_VectorArray* array) {
    lisp_u64 index = 0;
    lisp_Value* value = array->values[index];

    while (value != NULL) {
        lisp_Value_deref(state, value);
        index += 1;
        value = array->values[index];
    }
    free(array->values);
}

static lisp_VectorArray* lisp_VectorArray_new(void) {
    return lisp_VectorArray_constructor(
        (lisp_VectorArray*) malloc(sizeof(lisp_VectorArray)),
        lisp_Vector_alloc_values()
    );
}

static void lisp_VectorArray_delete(lisp_State* state, lisp_VectorArray* array) {
    lisp_VectorArray_destructor(state, array);
    free(array);
}

static void lisp_VectorArray_copy(lisp_VectorArray* a, lisp_VectorArray* b, lisp_u64 size) {
    for (lisp_u64 i = 0, il = size; i < il; i++) {
        a->values[i] = b->values[i];
    }
}

static void lisp_VectorArray_ref(lisp_VectorArray* array) {
    array->ref_count += 1;
}

static void lisp_VectorArray_deref(lisp_State* state, lisp_VectorArray* array) {
    array->ref_count -= 1;

    if (array->ref_count == 0) {
        lisp_VectorArray_delete(state, array);
    }
}


static struct lisp_Value** lisp_Vector_alloc_values(void) {
    lisp_Value** values = (lisp_Value**) malloc(LISP_VECTOR_SIZE * sizeof(lisp_Value*));
    for (lisp_u64 i = 0, il = LISP_VECTOR_SIZE; i < il; i++) {
        values[i] = NULL;
    }
    return values;
}

static lisp_VectorNode** lisp_Vector_alloc_nodes(void) {
    lisp_VectorNode** nodes = (lisp_VectorNode**) malloc(LISP_VECTOR_SIZE * sizeof(lisp_VectorNode*));
    for (lisp_u64 i = 0, il = LISP_VECTOR_SIZE; i < il; i++) {
        nodes[i] = NULL;
    }
    return nodes;
}


static lisp_VectorNode* lisp_VectorNode_constructor(
    lisp_VectorNode* node, lisp_VectorArray* values, lisp_VectorNode** nodes
) {
    node->ref_count = 1;
    if (values != NULL) {
        node->values = values;
        node->is_values = LISP_TRUE;
    } else {
        node->nodes = nodes;
        node->is_values = LISP_FALSE;
    }
    return node;
}

static void lisp_VectorNode_destructor(lisp_State* state, lisp_VectorNode* node) {
    if (node->is_values) {
        lisp_VectorArray_deref(state, node->values);
    } else {
        lisp_u64 index = 0;
        lisp_VectorNode* value = node->nodes[index];

        while (value != NULL) {
            lisp_VectorNode_deref(state, value);
            index += 1;
            value = node->nodes[index];
        }
        free(node->nodes);
    }
}

static lisp_VectorNode* lisp_VectorNode_new_values(void) {
    return lisp_VectorNode_constructor(
        (lisp_VectorNode*) malloc(sizeof(lisp_VectorNode)),
        lisp_VectorArray_new(),
        NULL
    );
}

static lisp_VectorNode* lisp_VectorNode_new_nodes(void) {
    return lisp_VectorNode_constructor(
        (lisp_VectorNode*) malloc(sizeof(lisp_VectorNode)),
        NULL,
        lisp_Vector_alloc_nodes()
    );
}

static lisp_VectorNode* lisp_VectorNode_new_tail(lisp_VectorArray* array) {
    return lisp_VectorNode_constructor(
        (lisp_VectorNode*) malloc(sizeof(lisp_VectorNode)),
        array,
        NULL
    );
}

static void lisp_VectorNode_delete(lisp_State* state, lisp_VectorNode* node) {
    lisp_VectorNode_destructor(state, node);
    free(node);
}

static lisp_VectorNode* lisp_VectorNode_copy(lisp_VectorNode* node, lisp_VectorNode* other, lisp_u64 size) {
    if (node->is_values) {
        lisp_VectorArray_copy(node->values, other->values, size);
    } else {
        for (lisp_u64 i = 0, il = size; i < il; i++) {
            node->nodes[i] = other->nodes[i];
        }
    }
    return node;
}

static lisp_VectorNode* lisp_VectorNode_clone(lisp_VectorNode* node, lisp_u64 size) {
    if (node->is_values) {
        return lisp_VectorNode_copy(lisp_VectorNode_new_values(), node, size);
    } else {
        return lisp_VectorNode_copy(lisp_VectorNode_new_nodes(), node, size);
    }
}

static void lisp_VectorNode_ref(lisp_VectorNode* node) {
    node->ref_count += 1;

    if (node->is_values) {
        lisp_VectorArray_ref(node->values);
    } else {
        lisp_u64 index = 0;
        lisp_VectorNode* value = node->nodes[index];

        while (value != NULL) {
            lisp_VectorNode_ref(value);
            index += 1;
            value = node->nodes[index];
        }
    }
}

static void lisp_VectorNode_deref(lisp_State* state, lisp_VectorNode* node) {
    node->ref_count -= 1;

    if (node->is_values) {
        lisp_VectorArray_deref(state, node->values);
    } else {
        lisp_u64 index = 0;
        lisp_VectorNode* value = node->nodes[index];

        while (value != NULL) {
            lisp_VectorNode_deref(state, value);
            index += 1;
            value = node->nodes[index];
        }
    }

    if (node->ref_count == 0) {
        lisp_VectorNode_delete(state, node);
    }
}

static void lisp_Vector_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Vector* vector = (lisp_Vector*) lisp_State_alloc(state, sizeof(lisp_Vector));
    value->value = vector;
    vector->value = value;
    vector->root = NULL;
    vector->tail = NULL;
    vector->size = 0;
    vector->shift = LISP_VECTOR_SHIFT;
}
static void lisp_Vector_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Vector* vector = (lisp_Vector*) value->value;

    if (vector->root != NULL) {
        lisp_VectorNode_deref(state, vector->root);
    }
    lisp_State_dealloc(state, value->value);
}

static lisp_Vector* lisp_Vector_constructor(
    lisp_Vector* vector, lisp_VectorNode* root, lisp_VectorArray* tail, lisp_u64 size, lisp_u64 shift
) {
    vector->root = root;
    vector->tail = tail;
    vector->size = size;
    vector->shift = shift;
    return vector;
}

static lisp_Value* lisp_Vector_from_mut_list(lisp_State* state, lisp_MutList* mut_list) {
    if (mut_list->size == 0) {
        return lisp_Value_ref(state->empty_vector);
    } else {
        lisp_Value* value = lisp_Value_new(state, state->type_vector);
        lisp_Vector_push_mut_list(state, (lisp_Vector*) value->value, mut_list);
        return value;
    }
}

static struct lisp_Value* lisp_Vector_from_list(lisp_State* state, lisp_List* list) {
    if (list->size == 0) {
        return lisp_Value_ref(state->empty_list);
    } else {
        lisp_Value* value = lisp_Value_new(state, state->type_vector);
        lisp_MutList* mut_list = lisp_MutList_new();
        lisp_ListNode* node = list->root;

        while (node != NULL) {
            lisp_MutList_push(mut_list, node->value);
            node = node->next;
        }

        lisp_Vector_push_mut_list(state, (lisp_Vector*) value->value, mut_list);
        lisp_MutList_delete(mut_list);

        return value;
    }
}

static lisp_Value* lisp_Vector_clone(lisp_State* state, lisp_Vector* vector) {
    lisp_Value* value = lisp_Value_new(state, state->type_vector);
    lisp_Vector_constructor((lisp_Vector*) value->value, vector->root, vector->tail, vector->size, vector->shift);
    return value;
}

static lisp_u64 lisp_Vector_size(lisp_Vector* vector) {
    return vector->size;
}

static lisp_u64 lisp_Vector_tail_off(lisp_u64 size) {
    if (size < LISP_VECTOR_SIZE) {
        return 0;
    } else {
        return ((size - 1) >> LISP_VECTOR_SHIFT) << LISP_VECTOR_SHIFT;
    }
}

static lisp_VectorNode* lisp_Vector_get_node(lisp_Vector* vector, lisp_u64 index) {
    lisp_VectorNode* node = vector->root;
    lisp_u64 level = vector->shift;

    while (level > 0) {
        node = node->nodes[(index >> level) & LISP_VECTOR_MASK];
        level = level - LISP_VECTOR_SHIFT;
    }

    return node;
}

static lisp_VectorArray* lisp_Vector_get_node_for(lisp_Vector* vector, lisp_u64 index) {
    if (index >= lisp_Vector_tail_off(vector->size)) {
        return vector->tail;
    } else {
        return lisp_Vector_get_node(vector, index)->values;
    }
}

static lisp_Value* lisp_Vector_find_index(lisp_Vector* vector, lisp_u64 index) {
    return lisp_Vector_get_node_for(vector, index)->values[index & LISP_VECTOR_MASK];
}

static lisp_Value* lisp_Vector_get(lisp_State* state, lisp_Vector* vector, lisp_u64 index) {
    if (index >= vector->size) {
        return state->nil;
    } else {
        return lisp_Vector_find_index(vector, index);
    }
}

static lisp_VectorNode* lisp_Vector_new_path_set(
    lisp_State* state, lisp_VectorNode* node, lisp_u64 size, lisp_u64 index, lisp_Value* value, lisp_u64 level
) {
    lisp_VectorNode* new_node = lisp_VectorNode_clone(node, ((size - 1) >> level) & LISP_VECTOR_MASK);

    if (level == 0) {
        new_node->values->values[index & LISP_VECTOR_MASK] = value;
    } else {
        lisp_u64 sub_index = (index >> level) & LISP_VECTOR_MASK;
        new_node->nodes[sub_index] = lisp_Vector_new_path_set(
            state, node->nodes[sub_index], size, index, value, level - LISP_VECTOR_SHIFT
        );
    }

    return new_node;
}

static lisp_Value* lisp_Vector_set(lisp_State* state, lisp_Vector* vector, lisp_u64 index, lisp_Value* value) {
    if (index >= vector->size) {
        return vector->value;
    } else {
        if (index >= lisp_Vector_tail_off(vector->size)) {
            lisp_VectorArray* tail = vector->tail;
            lisp_u64 masked_index = index & LISP_VECTOR_MASK;

            /* fixme */
            if (tail->values[masked_index] == value) {
                return vector->value;
            } else {
                lisp_VectorArray* new_tail = lisp_VectorArray_new();
                lisp_VectorArray_copy(new_tail, tail, (vector->size + 1) & LISP_VECTOR_MASK);
                new_tail->values[masked_index] = value;
                lisp_Value* new_vector = lisp_Vector_clone(state, vector);
                ((lisp_Vector*) new_vector->value)->tail = new_tail;
                return new_vector;
            }
        } else if (lisp_Vector_find_index(vector, index) == value) {
            return vector->value;
        } else {
            lisp_Value* new_vector = lisp_Vector_clone(state, vector);
            ((lisp_Vector*) new_vector->value)->root = lisp_Vector_new_path_set(state, vector->root, vector->size, index, value, vector->shift);
            return new_vector;
        }
    }
}

static lisp_VectorNode* lisp_Vector_new_path(lisp_State* state, lisp_VectorNode* node, lisp_u64 level) {
    if (level == 0) {
        return node;
    } else {
        lisp_VectorNode* new_node = lisp_VectorNode_new_nodes();
        new_node->nodes[0] = lisp_Vector_new_path(state, node, level - LISP_VECTOR_SHIFT);
        return new_node;
    }
}

static lisp_VectorNode* lisp_Vector_push_tail(
    lisp_State* state, lisp_VectorNode* parent, lisp_VectorNode* tail, lisp_u64 size, lisp_u64 level
) {
    lisp_u64 sub_index = ((size - 1) >> level) & LISP_VECTOR_MASK;
    lisp_VectorNode* new_node = lisp_VectorNode_clone(parent, sub_index);
    lisp_VectorNode* insert_node;

    if (level == LISP_VECTOR_SHIFT) {
        insert_node = tail;
    } else {
        lisp_VectorNode* child = parent->nodes[sub_index];

        if (child != NULL) {
            insert_node = lisp_Vector_push_tail(state, child, tail, size, level - LISP_VECTOR_SHIFT);
        } else {
            insert_node = lisp_Vector_new_path(state, tail, level - LISP_VECTOR_SHIFT);
        }
    }

    new_node->nodes[sub_index] = insert_node;

    return new_node;
}

static void lisp_Vector_push_value(lisp_State* state, lisp_Vector* vector, lisp_Value* value) {
    lisp_VectorNode* root = vector->root;
    lisp_u64 size = vector->size;
    lisp_u64 shift = vector->shift;

    if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        vector->tail->values[size & LISP_VECTOR_MASK] = value;
    } else {
        lisp_VectorNode* new_root;
        lisp_VectorNode* tail_node = lisp_VectorNode_new_tail(vector->tail);
        lisp_u64 new_shift = shift;

        if ((size >> LISP_VECTOR_SHIFT) > (1 << shift)) {
            new_root = lisp_VectorNode_new_nodes();
            new_root->nodes[0] = root;
            new_root->nodes[1] = lisp_Vector_new_path(state, tail_node, shift);
            new_shift += LISP_VECTOR_SHIFT;
        } else {
            new_root = lisp_Vector_push_tail(state, root, tail_node, size, shift);
        }

        lisp_VectorArray* new_tail = lisp_VectorArray_new();
        new_tail->values[0] = value;

        lisp_VectorNode_deref(state, root);
        lisp_VectorArray_deref(state, vector->tail);

        vector->tail = new_tail;
        vector->root = new_root;
        vector->shift = new_shift;
    }

    vector->size = size + 1;
}

static void lisp_Vector_push_mut_list(lisp_State* state, lisp_Vector* vector, lisp_MutList* mut_list) {
    lisp_VectorArray* tail = vector->tail;
    lisp_u64 size = vector->size;

    if (tail == NULL) {
        vector->tail = lisp_VectorArray_new();
    } else if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        lisp_VectorArray* new_tail = lisp_VectorArray_new();
        lisp_VectorArray_copy(tail, new_tail, (size + 1) & LISP_VECTOR_MASK);
        lisp_VectorArray_deref(state, tail);
        vector->tail = new_tail;
    }

    for (lisp_u64 i = 0, il = mut_list->size; i < il; i++) {
        lisp_Vector_push_value(state, vector, lisp_MutList_get(mut_list, i));
    }
}

static lisp_Value* lisp_Vector_push(lisp_State* state, lisp_Vector* vector, lisp_Value* value) {
    lisp_u64 size = vector->size;
    lisp_VectorArray* tail = vector->tail;

    lisp_Value* new_value = lisp_Vector_clone(state, vector);
    lisp_Vector* new_vector = (lisp_Vector*) new_value->value;

    if (tail == NULL) {
        new_vector->tail = lisp_VectorArray_new();
    } else if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        lisp_VectorArray* new_tail = lisp_VectorArray_new();
        lisp_VectorArray_copy(tail, new_tail, (size + 1) & LISP_VECTOR_MASK);
        lisp_VectorArray_deref(state, tail);
        new_vector->tail = new_tail;
    }

    lisp_Vector_push_value(state, new_vector, value);

    return new_value;
}

#endif
