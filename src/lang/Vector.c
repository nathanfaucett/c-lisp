#ifndef __LISP_LANG_VECTOR_C__
#define __LISP_LANG_VECTOR_C__


static lisp_VectorNode* lisp_VectorNode_values_constructor(lisp_VectorNode* node, lisp_Value** values) {
    node->ref_count = 1;
    node->size = 0;
    node->values = values;
    node->is_values = LISP_TRUE;
    return node;
}

static lisp_VectorNode* lisp_VectorNode_array_constructor(lisp_VectorNode* node, lisp_VectorNode** array) {
    node->ref_count = 1;
    node->size = 0;
    node->array = array;
    node->is_values = LISP_FALSE;
    return node;
}

static lisp_VectorNode* lisp_VectorNode_new_values(void) {
    return lisp_VectorNode_values_constructor(
        (lisp_VectorNode*) malloc(sizeof(lisp_VectorNode)),
        (lisp_Value**) malloc(LISP_VECTOR_SIZE * sizeof(lisp_Value*))
    );
}

static lisp_VectorNode* lisp_VectorNode_new_array(void) {
    return lisp_VectorNode_array_constructor(
        (lisp_VectorNode*) malloc(sizeof(lisp_VectorNode)),
        (lisp_VectorNode**) malloc(LISP_VECTOR_SIZE * sizeof(lisp_VectorNode*))
    );
}

static lisp_VectorNode* lisp_VectorNode_new_tail(lisp_Value* values) {
    return lisp_VectorNode_values_constructor(
        (lisp_VectorNode*) malloc(sizeof(lisp_VectorNode)), values
    );
}

static void lisp_VectorNode_delete(lisp_State* state, lisp_VectorNode* node) {
    if (node->values != NULL) {
        for (lisp_u32 i = 0, il = node->size; i < il; i++) {
            lisp_Value_deref(state, node->values[i]);
        }
    }
    if (node->is_values) {
        free(node->values);
    } else {
        free(node->array);
    }
    free(node);
}

static lisp_VectorNode* lisp_VectorNode_copy(lisp_VectorNode* node, lisp_VectorNode* other, lisp_u32 size) {
    if (node->is_values) {
        values_array_copy(node->values, other->values, 0, size, 0);
    } else {
        vector_nodes_array_copy(node->array, other->array, 0, size, 0);
    }
    return node;
}

static lisp_VectorNode* lisp_VectorNode_clone(lisp_VectorNode* node, lisp_u32 size) {
    if (node->is_values) {
        return lisp_VectorNode_copy(lisp_VectorNode_new_values(), node, size);
    } else {
        return lisp_VectorNode_copy(lisp_VectorNode_new_array(), node, size);
    }
}

static void lisp_VectorNode_ref(lisp_VectorNode* node) {
    node->ref_count += 1;

    if (node->array != NULL) {
        for (lisp_u32 i = 0, il = node->size; i < il; i++) {
            lisp_VectorNode_ref(node->array[i]);
        }
    }
}

static void lisp_VectorNode_deref(lisp_State* state, lisp_VectorNode* node) {
    node->ref_count -= 1;

    if (node->array != NULL) {
        for (lisp_u32 i = 0, il = node->size; i < il; i++) {
            lisp_VectorNode_deref(state, node->array[i]);
        }
    }

    if (node->ref_count == 0) {
        lisp_VectorNode_delete(state, node);
    }
}


static lisp_Vector* lisp_Vector_constructor(
    lisp_Vector* vector, lisp_VectorNode* root, lisp_Value** tail, lisp_u32 size, lisp_u32 shift
) {
    vector->root = root;
    vector->tail = tail;
    vector->size = size;
    vector->shift = shift;
    return vector;
}

static void lisp_Vector_destructor(lisp_State* state, lisp_Vector* vector) {
    if (vector->root != NULL) {
        lisp_VectorNode_deref(state, vector->root);
    }
}

static lisp_Value* lisp_Vector_from_array(lisp_State* state, lisp_Array* array) {
    lisp_u32 size = lisp_Array_size(array);

    if (size == 0) {
        return lisp_Value_list(state);
    } else {
        lisp_Value* list_value = lisp_List_internal_new(state);
        return list_value;
    }
}

static lisp_Value* lisp_Vector_internal_new(lisp_State* state) {
    lisp_Value* value = lisp_State_alloc(state);
    value->type = LISP_TYPE_VECTOR;
    value->list.value = value;
    value->ref_count = 1;
    return value;
}

static lisp_Value* lisp_Vector_clone(lisp_State* state, lisp_Vector* vector) {
    lisp_Value* value = lisp_Vector_internal_new(state);
    lisp_Vector_constructor(&value->vector, vector->root, vector->tail, vector->size, vector->shift);
    return value;
}

static lisp_u32 lisp_Vector_tail_off(lisp_u32 size) {
    if (size < LISP_VECTOR_SIZE) {
        return 0;
    } else {
        return ((size - 1) >> LISP_VECTOR_SHIFT) << LISP_VECTOR_SHIFT;
    }
}

static lisp_VectorNode* lisp_Vector_get_node(lisp_Vector* vector, lisp_u32 index) {
    lisp_VectorNode* node = vector->root;
    lisp_u32 level = vector->shift;

    while (level > 0) {
        node = node->array[(index >> level) & LISP_VECTOR_MASK];
        level = level - LISP_VECTOR_SHIFT;
    }

    return node;
}

static lisp_Value** lisp_Vector_get_array_for(lisp_Vector* vector, lisp_u32 index) {
    if (index >= lisp_Vector_tail_off(vector->size)) {
        return vector->tail;
    } else {
        return lisp_Vector_get_node(vector, index)->values;
    }
}

static lisp_Value* lisp_Vector_find_index(lisp_Vector* vector, lisp_u32 index) {
    return lisp_Vector_get_array_for(vector, index)[index & LISP_VECTOR_MASK];
}

static lisp_Value* lisp_Vector_get(lisp_State* state, lisp_Vector* vector, lisp_u32 index) {
    if (index >= vector->size) {
        return state->nil;
    } else {
        return lisp_Vector_find_index(vector, index);
    }
}

static lisp_VectorNode* lisp_Vector_new_path_set(
    lisp_VectorNode* node, lisp_u32 size, lisp_u32 index, lisp_Value* value, lisp_u32 level
) {
    lisp_VectorNode* new_node = lisp_VectorNode_clone(node, ((size - 1) >> level) & LISP_VECTOR_MASK);

    if (level == 0) {
        new_node->values[index & LISP_VECTOR_MASK] = value;
    } else {
        lisp_u32 sub_index = (index >> level) & LISP_VECTOR_MASK;
        new_node->array[sub_index] = lisp_Vector_new_path_set(
            node->array[sub_index], size, index, value, level - LISP_VECTOR_SHIFT
        );
    }

    return new_node;
}

static lisp_Value* lisp_Vector_set(lisp_State* state, lisp_Vector* vector, lisp_u32 index, lisp_Value* value) {
    if (index >= vector->size) {
        return vector->value;
    } else {
        if (index >= lisp_Vector_tail_off(vector->size)) {
            lisp_Value** tail = vector->tail;
            lisp_u32 masked_index = index & LISP_VECTOR_MASK;

            if (lisp_Value_equal(tail[masked_index], value)) {
                return vector->value;
            } else {
                lisp_Value** new_tail = (lisp_Value**) malloc(LISP_VECTOR_SIZE * sizeof(lisp_Value*));
                values_array_copy(new_tail, tail, 0, (vector->size + 1) & LISP_VECTOR_MASK, 0);
                new_tail[masked_index] = value;
                lisp_Value* new_vector = lisp_Vector_clone(state, vector);
                new_vector->vector.tail = new_tail;
                return new_vector;
            }
        } else if (lisp_Value_equal(lisp_Vector_find_index(vector, index), value)) {
            return vector->value;
        } else {
            lisp_Value* new_vector = lisp_Vector_clone(state, vector);
            new_vector->vector.root = lisp_Vector_new_path_set(vector->root, vector->size, index, value, vector->shift);
            return new_vector;
        }
    }
}

static lisp_VectorNode* lisp_Vector_new_path(lisp_VectorNode* node, lisp_u32 level) {
    if (level == 0) {
        return node;
    } else {
        lisp_VectorNode* new_node = lisp_VectorNode_new_array();
        new_node->array[0] = lisp_Vector_new_path(node, level - LISP_VECTOR_SHIFT);
        return new_node;
    }
}

static lisp_VectorNode* lisp_Vector_push_tail(
    lisp_VectorNode* parent, lisp_VectorNode* tail, lisp_u32 size, lisp_u32 level
) {
    lisp_u32 sub_index = ((size - 1) >> level) & LISP_VECTOR_MASK;
    lisp_VectorNode* new_node = lisp_VectorNode_clone(parent, sub_index);
    lisp_VectorNode* insert_node;

    if (level == LISP_VECTOR_SHIFT) {
        insert_node = tail;
    } else {
        lisp_VectorNode* child = parent->array[sub_index];

        if (child != NULL) {
            insert_node = lisp_Vector_push_tail(child, tail, size, level - LISP_VECTOR_SHIFT);
        } else {
            insert_node = lisp_Vector_new_path(tail, level - LISP_VECTOR_SHIFT);
        }
    }

    new_node->array[sub_index] = insert_node;

    return new_node;
}

static void lisp_Vector_push_value(lisp_Vector* vector, lisp_Value* value) {
    lisp_VectorNode* root = vector->root;
    lisp_u32 size = vector->size;
    lisp_u32 shift = vector->shift;

    if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        vector->tail[size & LISP_VECTOR_MASK] = value;
    } else {
        lisp_VectorNode* new_root;
        lisp_VectorNode* tail_node = lisp_VectorNode_new_tail(vector->tail);
        lisp_u32 new_shift = shift;

        if ((size >> LISP_VECTOR_SHIFT) > (1 << shift)) {
            new_root = lisp_VectorNode_new_array();
            new_root.array[0] = root;
            new_root.array[1] = lisp_Vector_new_path(tail_node, shift);
            new_shift += SHIFT;
        } else {
            new_root = lisp_Vector_push_tail(root, tail_node, size, shift);
        }

        lisp_Value** new_tail = (lisp_Value**) malloc(LISP_VECTOR_SIZE * sizeof(lisp_Value*));
        new_tail[0] = value;

        vector->tail = new_tail;
        vector->root = new_root;
        vector->shift = new_shift;
    }

    vector->size = size + 1;
}

static void lisp_Vector_push_array(lisp_Vector* vector, lisp_Array* array) {
    lisp_Value** tail = vector->tail;
    lisp_u32 size = vector->size;
    lisp_u32 size = vector->size;

    if (tail == NULL) {
        vector->tail = (lisp_Value**) malloc(LISP_VECTOR_SIZE * sizeof(lisp_Value*));
    } else if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        lisp_Value** new_tail = (lisp_Value**) malloc(LISP_VECTOR_SIZE * sizeof(lisp_Value*));
        values_array_copy(vector->tail, new_tail, 0, (size + 1) & LISP_VECTOR_MASK, 0);
        vector->tail = new_tail;
    }

    for (lisp_u32 i = 0, il = size; i < il; i++) {
        lisp_Vector_push_value(vector, lisp_Array_get(array, i));
    }
}

static lisp_Value* lisp_Vector_to_string(lisp_State* state, lisp_Vector* vector) {
    return lisp_Value_string_from_cstring(state, "[Vector]");
}

static lisp_bool lisp_Vector_equal(lisp_Vector* a, lisp_Vector* b) {
    if (a->size != b->size) {
        return LISP_FALSE;
    } else {
        for (lisp_u32 i = 0, il = a->size; i < il; i++) {
            if (!lisp_Value_equal(lisp_Vector_find_index(a, i), lisp_Vector_find_index(b, i))) {
                return LISP_FALSE;
            }
        }
        return LISP_TRUE;
    }
}

#endif
