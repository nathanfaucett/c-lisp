#ifndef __LISP_LANG_VECTOR_C__
#define __LISP_LANG_VECTOR_C__


static void lisp_Vector_alloc(lisp_State* state, lisp_Object* object) {
    lisp_Vector* vector = (lisp_Vector*) object->data;
    vector->self = object;
    vector->root = NULL;
    vector->tail = NULL;
    vector->size = 0;
    vector->shift = LISP_VECTOR_SHIFT;
}
static void lisp_Vector_mark(lisp_Object* object) {
    lisp_Vector* vector = (lisp_Vector*) object->data;

    if (vector->root != NULL) {
        lisp_VectorNode_mark(vector->root);
    }
}

static lisp_Object* lisp_Vector_new(lisp_State* state, lisp_Object* template) {
    lisp_Object* object = lisp_Object_boot_template_size(state, state->Vector, template, sizeof(lisp_Vector));
    lisp_Vector_alloc(state, object);
    return object;
}
static lisp_Object* lisp_Vector_new_type(lisp_State* state, lisp_Object* Type) {
    lisp_Object* object = lisp_Object_boot_size(state, Type, sizeof(lisp_Vector));
    lisp_Vector_alloc(state, object);
    return object;
}
static lisp_Object* lisp_Vector_clone(lisp_State* state, lisp_Vector* vector) {
    lisp_Object* object = lisp_Vector_new_type(state, vector->self->type);
    lisp_Vector* new_vector = (lisp_Vector*) object->data;
    new_vector->self = object;
    new_vector->root = vector->root;
    new_vector->tail = vector->tail;
    new_vector->size = vector->size;
    new_vector->shift = vector->shift;
    return object;
}

/*
static lisp_Object* lisp_Vector_from_ascii(lisp_State* state, lisp_char* ascii) {
    lisp_Object* object = lisp_Vector_new(state, lisp_Annotation_new(state, state->Char));
    lisp_Vector* vector = (lisp_Vector*) object->data;

    lisp_Object* ch;
    uintsize i = 0, il = lisp_ascii_size(ascii);
    for (; i < il; i++) {
        ch = lisp_Object_boot_size(state, state->Char, 4);
        LISP_OBJECT_SET_DATA(ch, lisp_u32, ascii[i]);
        lisp_Vector_mut_push(state, vector, ch);
    }

    return object;
}
*/
static void lisp_Vector_mut_set_size(lisp_State* state, lisp_Vector* vector, uintsize size) {
    uintsize i = 0, il = size;
    for (; i < il; i++) {
        lisp_Vector_mut_push(state, vector, state->nil_value);
    }
}

static lisp_Object* lisp_Vector_concat(lisp_State* state, lisp_Vector* a, lisp_Vector* b) {
    if (a->size == 0) {
        return b->self;
    } else if (b->size == 0) {
        return a->self;
    } else {
        lisp_Object* object = lisp_Vector_new_type(state, a->self->type);
        lisp_Vector* vector = (lisp_Vector*) object->data;

        uintsize i = 0, il = a->size;
        for (; i < il; i++) {
            lisp_Vector_mut_push(state, vector, lisp_Vector_get(state, a, i));
        }
        i = 0, il = b->size;
        for (; i < il; i++) {
            lisp_Vector_mut_push(state, vector, lisp_Vector_get(state, b, i));
        }

        return object;
    }
}
static uintsize lisp_Vector_index_of(lisp_State* state, lisp_Vector* vector, lisp_Object* value) {
    uintsize i = 0, il = vector->size;

    for (; i < il; i++) {
        if (lisp_Object_equal(state, lisp_Vector_get(state, vector, i), value)) {
            return i + 1;
        }
    }

    return 0;
}

static uintsize lisp_Vector_tail_off(uintsize size) {
    if (size < LISP_VECTOR_SIZE) {
        return 0;
    } else {
        return ((size - 1) >> LISP_VECTOR_SHIFT) << LISP_VECTOR_SHIFT;
    }
}
static lisp_VectorNode* lisp_Vector_find_node(lisp_Vector* vector, uintsize index) {
    if (index >= lisp_Vector_tail_off(vector->size)) {
        return vector->tail;
    } else {
        lisp_VectorNode* node = vector->root;
        uintsize level = vector->shift;

        while (level > 0) {
            node = node->nodes[(index >> level) & LISP_VECTOR_MASK];
            level = level - LISP_VECTOR_SHIFT;
        }

        return node;
    }
}
static lisp_Object* lisp_Vector_get(lisp_State* state, lisp_Vector* vector, uintsize index) {
    if (index < vector->size) {
        return lisp_Vector_find_node(vector, index)->values[index & LISP_VECTOR_MASK];
    } else {
        return state->nil_value;
    }
}

static lisp_VectorNode* lisp_Vector_new_path_set(
    lisp_State* state, lisp_VectorNode* node, uintsize size, uintsize index, lisp_Object* value, uintsize level
) {
    lisp_VectorNode* new_node = lisp_VectorNode_clone(state, node, ((size - 1) >> level) & LISP_VECTOR_MASK);

    if (level == 0) {
        new_node->values[index & LISP_VECTOR_MASK] = value;
    } else {
        uintsize sub_index = (index >> level) & LISP_VECTOR_MASK;
        new_node->nodes[sub_index] = lisp_Vector_new_path_set(
            state, node->nodes[sub_index], size, index, value, level - LISP_VECTOR_SHIFT
        );
    }

    return node;
}
static lisp_Object* lisp_Vector_set(lisp_State* state, lisp_Vector* vector, uintsize index, lisp_Object* value) {
    uintsize size = vector->size;

    if (index < size) {
        if (index >= lisp_Vector_tail_off(size)) {
            lisp_VectorNode* tail = vector->tail;
            uintsize masked_index = index & LISP_VECTOR_MASK;

            if (lisp_Object_equal(state, tail->values[masked_index], value)) {
                return vector->self;
            } else {
                lisp_Object* new_vector_object = lisp_Vector_clone(state, vector);
                lisp_Vector* new_vector = (lisp_Vector*) new_vector_object->data;

                tail = lisp_VectorNode_clone(state, tail, (size + 1) & LISP_VECTOR_MASK);
                tail->values[masked_index] = value;
                new_vector->tail = tail;

                return new_vector_object;
            }
        } else if (lisp_Object_equal(state, lisp_Vector_get(state, vector, index), value)) {
            return vector->self;
        } else {
            lisp_Object* new_vector_object = lisp_Vector_clone(state, vector);
            lisp_Vector* new_vector = (lisp_Vector*) new_vector_object->data;
            new_vector->root = lisp_Vector_new_path_set(state, vector->root, size, index, value, vector->shift);
            return new_vector_object;
        }
    } else {
        return vector->self;
    }
}
static void lisp_Vector_mut_set(lisp_Vector* vector, uintsize index, lisp_Object* value) {
    lisp_VectorNode* node = lisp_Vector_find_node(vector, index);

    if (node != NULL) {
        node->values[index & LISP_VECTOR_MASK] = value;
    }
}

static lisp_VectorNode* lisp_Vector_new_path(lisp_State* state, lisp_VectorNode* node, uintsize level) {
    if (level == 0) {
        return node;
    } else {
        lisp_VectorNode* new_node = lisp_VectorNode_new_nodes(state);
        new_node->nodes[0] = lisp_Vector_new_path(state, node, level - LISP_VECTOR_SHIFT);
        return new_node;
    }
}
static lisp_VectorNode* lisp_Vector_push_tail(
    lisp_State* state, lisp_VectorNode* parent, lisp_VectorNode* tail, uintsize size, uintsize level
) {
    uintsize sub_index = ((size - 1) >> level) & LISP_VECTOR_MASK;
    lisp_VectorNode* new_node = lisp_VectorNode_new_nodes(state);
    lisp_VectorNode* node_to_insert = NULL;

    if (level == LISP_VECTOR_SHIFT) {
        node_to_insert = tail;
    } else {
        lisp_VectorNode* child = parent->nodes[sub_index];

        if (child == NULL) {
            node_to_insert = lisp_Vector_new_path(state, tail, level - LISP_VECTOR_SHIFT);
        } else {
            node_to_insert = lisp_Vector_push_tail(state, child, tail, size, level - LISP_VECTOR_SHIFT);
        }
    }

    new_node->nodes[sub_index] = node_to_insert;

    return new_node;
}
static void lisp_Vector_mut_push(lisp_State* state, lisp_Vector* vector, lisp_Object* value) {
    lisp_VectorNode* root = vector->root;
    uintsize size = vector->size;
    uintsize shift = vector->shift;

    if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        if (vector->tail == NULL) {
            vector->tail = lisp_VectorNode_new_values(state);
        }
        vector->tail->values[size & LISP_VECTOR_MASK] = value;
    } else {
        lisp_VectorNode* new_root = NULL;
        uintsize new_shift = shift;

        if ((size >> LISP_VECTOR_SHIFT) > (1 << shift)) {
            new_root = lisp_VectorNode_new_nodes(state);
            new_root->nodes[0] = root;
            new_root->nodes[1] = lisp_Vector_new_path(state, vector->tail, shift);
            new_shift += LISP_VECTOR_SHIFT;
        } else {
            new_root = lisp_Vector_push_tail(state, root, vector->tail, size, shift);
        }

        lisp_VectorNode* new_tail = lisp_VectorNode_new_values(state);
        new_tail->values[0] = value;

        vector->root = new_root;
        vector->tail = new_tail;
        vector->shift = new_shift;
    }

    vector->size = size + 1;
}
static lisp_Object* lisp_Vector_push(lisp_State* state, lisp_Vector* vector, lisp_Object* value) {
    lisp_Object* new_vector_object = lisp_Vector_clone(state, vector);
    lisp_Vector* new_vector = (lisp_Vector*) new_vector_object->data;
    uintsize size = vector->size;

    if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        new_vector->tail = lisp_VectorNode_clone(state, vector->tail, (size + 1) & LISP_VECTOR_MASK);
    }

    lisp_Vector_mut_push(state, new_vector, value);

    return new_vector_object;
}

static lisp_VectorNode* lisp_Vector_pop_tail(lisp_State* state, lisp_VectorNode* node, uintsize size, uintsize level) {
    uintsize sub_index = ((size - 1) >> level) & LISP_VECTOR_MASK;

    if (level > LISP_VECTOR_SHIFT) {
        lisp_VectorNode* new_child = lisp_Vector_pop_tail(
            state, node->nodes[sub_index], size, level - LISP_VECTOR_SHIFT
        );

        if (new_child == NULL) {
            return NULL;
        } else {
            lisp_VectorNode* new_node = lisp_VectorNode_clone(state, node, sub_index);
            new_node->nodes[sub_index] = new_child;
            return new_node;
        }
    } else if (sub_index == 0) {
        return NULL;
    } else {
        return lisp_VectorNode_clone(state, node, sub_index);
    }
}
static lisp_Object* lisp_Vector_pop(lisp_State* state, lisp_Vector* vector) {
    uintsize size = vector->size;

    if (size == 0) {
        return vector->self;
    } else if (size == 1) {
        return lisp_Vector_new_type(state, vector->self->type);
    } else {
        lisp_Object* new_vector_object = lisp_Vector_new_type(state, vector->self->type);
        lisp_Vector* new_vector = (lisp_Vector*) new_vector_object->data;

        lisp_VectorNode* new_root = NULL;
        lisp_VectorNode* new_tail = NULL;
        uintsize new_shift;

        if ((size - lisp_Vector_tail_off(size)) > 1) {
            new_tail = lisp_VectorNode_clone(state, vector->tail, (size - 1) & LISP_VECTOR_MASK);
            new_root = vector->root;
            new_shift = vector->shift;
        } else {
            new_tail = lisp_Vector_find_node(vector, size - 2);

            uintsize shift = vector->shift;
            new_root = lisp_Vector_pop_tail(state, vector->root, size, shift);
            new_shift = shift;

            if (new_root != NULL) {
                if (shift > LISP_VECTOR_SHIFT && new_root->nodes[1] == NULL) {
                    new_root = new_root->nodes[0];
                    new_shift -= LISP_VECTOR_SHIFT;
                }
            }
        }

        new_vector->root = new_root;
        new_vector->tail = new_tail;
        new_vector->size = size - 1;
        new_vector->shift = new_shift;

        return new_vector_object;
    }
}

static lisp_Object* lisp_Vector_unshift(lisp_State* state, lisp_Vector* vector, lisp_Object* value) {
    uintsize size = vector->size;

    if (size != 0) {
        lisp_GCHeader* gc_header = lisp_State_alloc(state, (size + 1) * sizeof(lisp_Object*));
        lisp_Object** array = (lisp_Object**) gc_header->data;

        uintsize i = 0, il = size, j = 1;
        for (; i < il; i++, j++) {
            array[j] = lisp_Vector_get(state, vector, i);
        }
        array[0] = value;

        lisp_Object* new_vector_object = lisp_Vector_new_type(state, vector->self->type);
        lisp_Vector* new_vector = (lisp_Vector*) new_vector_object->data;

        for (i = 0, il = size + 1; i < il; i++) {
            lisp_Vector_mut_push(state, new_vector, array[i]);
        }
        lisp_State_dealloc(state, gc_header);

        return new_vector_object;
    } else {
        return lisp_Vector_push(state, vector, value);
    }
}

static lisp_Object* lisp_Vector_remove(lisp_State* state, lisp_Vector* vector, uintsize index) {
    uintsize size = vector->size;

    if (index < size) {
        lisp_GCHeader* gc_header = lisp_State_alloc(state, (size - 1) * sizeof(lisp_Object*));
        lisp_Object** array = (lisp_Object**) gc_header->data;

        uintsize i = 0, il = index, j = 0;
        for (; i < il; i++, j++) {
            array[j] = lisp_Vector_get(state, vector, i);
        }
        for (i = index + 1, il = size; i < il; i++, j++) {
            array[j] = lisp_Vector_get(state, vector, i);
        }

        lisp_Object* new_vector_object = lisp_Vector_new_type(state, vector->self->type);
        lisp_Vector* new_vector = (lisp_Vector*) new_vector_object->data;

        for (i = 0, il = size - 1; i < il; i++) {
            lisp_Vector_mut_push(state, new_vector, array[i]);
        }
        lisp_State_dealloc(state, gc_header);

        return new_vector_object;
    } else {
        return vector->self;
    }
}
static void lisp_Vector_mut_remove(lisp_State* state, lisp_Vector* vector, uintsize index) {
    uintsize size = vector->size;

    if (index < size) {
        lisp_GCHeader* gc_header = lisp_State_alloc(state, size * sizeof(lisp_Object*));
        lisp_Object** array = (lisp_Object**) gc_header->data;

        uintsize i = 0, il = index, j = 0;
        for (; i < il; i++, j++) {
            array[j] = lisp_Vector_get(state, vector, i);
        }
        for (i = index + 1, il = size; i < il; i++, j++) {
            array[j] = lisp_Vector_get(state, vector, i);
        }

        vector->root = NULL;
        vector->tail = NULL;
        vector->size = 0;
        vector->shift = LISP_VECTOR_SHIFT;

        for (i = 0, il = size - 1; i < il; i++) {
            lisp_Vector_mut_push(state, vector, array[i]);
        }
        lisp_State_dealloc(state, gc_header);
    }
}

static bool lisp_Vector_equal(lisp_State* state, lisp_Vector* a, lisp_Vector* b) {
    if (a == b) {
        return true;
    } else if (a->size == b->size) {
        uintsize i = 0, il = a->size;

        for (; i < il; i++) {
            if (!lisp_Object_equal(state, lisp_Vector_get(state, a, i), lisp_Vector_get(state, b, i))) {
                return false;
            }
        }

        return true;
    } else {
        return false;
    }
}


#endif
