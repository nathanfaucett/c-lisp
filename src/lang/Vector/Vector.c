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

static lisp_Object* lisp_Vector_new(lisp_State* state) {
    lisp_Object* object = lisp_Object_boot_size(state, state->Vector, sizeof(lisp_Vector));
    lisp_Vector_alloc(state, object);
    return object;
}
static lisp_Object* lisp_Vector_clone(lisp_State* state, lisp_Vector* vector) {
    lisp_Object* object = lisp_Object_boot_size(state, state->Vector, sizeof(lisp_Vector));
    lisp_Vector* new_vector = (lisp_Vector*) object->data;
    new_vector->self = object;
    new_vector->root = vector->root;
    new_vector->tail = vector->tail;
    new_vector->size = vector->size;
    new_vector->shift = vector->shift;
    return object;
}

static lisp_size lisp_Vector_tail_off(lisp_size size) {
    if (size < LISP_VECTOR_SIZE) {
        return 0;
    } else {
        return ((size - 1) >> LISP_VECTOR_SHIFT) << LISP_VECTOR_SHIFT;
    }
}
static lisp_Object* lisp_Vector_find_node(lisp_Vector* vector, lisp_size index) {
    if (index >= lisp_Vector_tail_off(vector->size)) {
        return vector->tail;
    } else {
        lisp_Object* node = vector->root;
        lisp_size level = vector->shift;

        while (level > 0) {
            node = ((lisp_VectorNode*) node->data)->array[(index >>> level) & LISP_VECTOR_MASK];
            level = level - LISP_VECTOR_SHIFT;
        }

        return node;
    }
}
static lisp_Object* lisp_Vector_get(lisp_State* state, lisp_Vector* vector, lisp_size index) {
    if (index < vector->size) {
        return ((lisp_VectorNode*) lisp_Vector_find_node(vector, index)->data)->array[index & MASK];
    } else {
        return state->nil;
    }
}

static lisp_Object* lisp_Vector_new_path_set(
    lisp_State* state, lisp_Object* node_object, lisp_size size, lisp_size index, lisp_Object* value, lisp_size level
) {
    lisp_Object* new_node_object = lisp_VectorNode_clone(state, node_object, ((size - 1) >>> level) & LISP_VECTOR_MASK);
    lisp_VectorNode* new_node = (lisp_VectorNode*) new_node_object->data;

    if (level == 0) {
        new_node->array[index & LISP_VECTOR_MASK] = value;
    } else {
        lisp_size sub_index = (index >>> level) & LISP_VECTOR_MASK;
        new_node->array[sub_index] = lisp_Vector_new_path_set(
            node->array[sub_index], size, index, value, level - LISP_VECTOR_SHIFT
        );
    }

    return new_node_object;
}
static lisp_Object* lisp_Vector_set(lisp_State* state, lisp_Vector* vector, lisp_size index, lisp_Object* value) {
    lisp_size size = vector->size;

    if (index < size) {
        if (index >= lisp_Vector_tail_off(size)) {
            lisp_VectorNode* tail = (lisp_VectorNode*) vector->tail->data;
            lisp_size masked_index = index & MASK;

            if (is_Object_equal(state, tail->array[masked_index], value)) {
                return vector->self;
            } else {
                lisp_Object* new_vector_object = lisp_Vector_clone(state, vector);
                lisp_Vector* new_vector = (lisp_Vector*) new_vector_object->data;

                tail = lisp_VectorNode_clone(state, tail, (size + 1) & MASK);
                tail->array[masked_index] = value;
                new_vector->tail = tail;

                return new_vector_object;
            }
        } else if (is_Object_equal(state, lisp_Vector_get(vector, index), value)) {
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

static lisp_Object* lisp_Vector_new_path(lisp_State* state, lisp_Object* node_object, lisp_size level) {
    if (level == 0) {
        return node_object;
    } else {
        lisp_Object* new_node_object = lisp_VectorNode_new(state);
        lisp_VectorNode* new_node = (lisp_VectorNode*) new_vector_object->data;
        new_node->array[0] = lisp_Vector_new_path(state, new_node, level - LISP_VECTOR_SHIFT);
        return new_node_object;
    }
}
static lisp_Object* lisp_Vector_push_tail(
    lisp_State* state, lisp_Object* parent_object, tail_object, lisp_size size, lisp_size level
) {
    lisp_size sub_index = ((size - 1) >>> level) & LISP_VECTOR_MASK;
    lisp_Object* new_node_object = lisp_VectorNode_new(state);
    lisp_Object* node_to_insert = NULL;

    if (level == LISP_VECTOR_SHIFT) {
        node_to_insert = tail_object;
    } else {
        lisp_Object* child = ((lisp_VectorNode*) parent_object->data)->array[sub_index];

        if (child == NULL) {
            node_to_insert = lisp_Vector_new_path(state, tail_object, level - SHIFT);
        } else {
            node_to_insert = lisp_Vector_push_tail(state, child, tail_object, size, level - SHIFT);
        }
    }

    ((lisp_VectorNode*) new_node_object->data)->array[sub_index] = node_to_insert;

    return new_node_object;
}
static lisp_Object* lisp_Vector_mut_push(lisp_State* state, lisp_Vector* vector, lisp_Object* value) {
    lisp_Object* root = vector->root;
    lisp_size size = vector->size;
    lisp_size shift = vector->shift;

    if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        ((lisp_VectorNode*) vector->tail->data)->array[size & LISP_VECTOR_MASK] = value;
    } else {
        lisp_Object* new_root_object = NULL;
        lisp_VectorNode* new_root = NULL;
        lisp_size new_shift = shift;

        if ((size >> LISP_VECTOR_SHIFT) > (1 << shift)) {
            new_root_object = lisp_VectorNode_new(state);
            new_root = (lisp_VectorNode*) new_root_object->data;
            new_root->array[0] = root;
            new_root->array[1] = lisp_Vector_new_path(state, vector->tail, shift);
            new_shift += LISP_VECTOR_SHIFT;
        } else {
            new_root_object = lisp_Vector_push_tail(state, root, vector->tail, size, shift);
            new_root = (lisp_VectorNode*) new_root_object->data;
        }

        lisp_Object* new_tail_object = lisp_VectorNode_new(state);
        ((lisp_VectorNode*) new_tail_object->data)->array[0] = value;
        vector->tail = new_tail_object;

        vector->root = new_root_object;
        vector->shift = new_shift;
    }

    vector->size = size + 1;

    return vector;
}
static lisp_Object* lisp_Vector_push(lisp_State* state, lisp_Vector* vector, lisp_Object* value) {
    lisp_size size = vector->size;
    lisp_Object* new_vector_object = lisp_Vector_clone(state, vector);
    lisp_Vector* new_vector = (lisp_Vector*) new_vector_object->data;

    if (new_vector->tail == NULL) {
        new_vector->tail = lisp_VectorNode_new(state);
    } else if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        new_vector->tail = lisp_VectorNode_clone(state, vector->tail);
    }

    lisp_Vector_mut_push(state, new_vector, value);

    return new_vector_object;
}


#endif
