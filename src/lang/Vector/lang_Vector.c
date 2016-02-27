#ifndef __LISP_LANG_VECTOR_C__
#define __LISP_LANG_VECTOR_C__


static lisp_Object* lisp_Vector_init(lisp_State* state, lisp_Object* vector) {
    lisp_Object** values = (lisp_Object**) vector->data;
    values[LISP_IDX_VECTOR_ROOT] = state->nil;
    values[LISP_IDX_VECTOR_TAIL] = state->nil;
    values[LISP_IDX_VECTOR_SIZE] = lisp_Number_new_UInt(state, 0);
    values[LISP_IDX_VECTOR_SHIFT] = lisp_Number_new_UInt(state, LISP_VECTOR_SHIFT);
    return vector;
}
static lisp_Object* lisp_Vector_new_type(lisp_State* state, lisp_Object* type) {
    lisp_Object* object = lisp_boot_object_size(state, type, sizeof(void*) * 4);
    return lisp_Vector_init(state, object);
}

uintsize lisp_Vector_size(lisp_Object* vector) {
    return LISP_OBJECT_GET_DATA(((lisp_Object**) vector->data)[LISP_IDX_VECTOR_SIZE], uintsize);
}

static lisp_Object* lisp_Vector_clone(lisp_State* state, lisp_Object* vector) {
    lisp_Object** values = (lisp_Object**) vector->data;
    lisp_Object* new_vector = lisp_Vector_new_type(state, vector->type);
    lisp_Object** new_vector_values = (lisp_Object**) new_vector->data;

    new_vector_values[LISP_IDX_VECTOR_ROOT] = values[LISP_IDX_VECTOR_ROOT];
    new_vector_values[LISP_IDX_VECTOR_TAIL] = values[LISP_IDX_VECTOR_TAIL];
    new_vector_values[LISP_IDX_VECTOR_SIZE] = values[LISP_IDX_VECTOR_SIZE];
    new_vector_values[LISP_IDX_VECTOR_SHIFT] = values[LISP_IDX_VECTOR_SHIFT];

    return new_vector;
}

lisp_Object* lisp_Vector_from_ascii(lisp_State* state, char* ascii) {
    lisp_Object* vector = lisp_Vector_new_type(state, state->CharVector);

    lisp_Object* ch = NULL;
    uintsize i = 0;
    char ascii_ch = ascii[i];

    while (ascii_ch != '\0') {
        ch = lisp_boot_object_size(state, state->Char, 4);
        LISP_OBJECT_SET_DATA(ch, uint32, ascii_ch);
        lisp_Vector_mut_push(state, vector, ch);
        i += 1;
        ascii_ch = ascii[i];
    }

    return vector;
}
static void lisp_Vector_mut_set_size(lisp_State* state, lisp_Object* vector, uintsize size) {
    uintsize i = 0, il = size;
    for (; i < il; i++) {
        lisp_Vector_mut_push(state, vector, state->nil);
    }
}

lisp_Object* lisp_Vector_concat(lisp_State* state, lisp_Object* a, lisp_Object* b) {
    lisp_Object** avalues = (lisp_Object**) a->data;
    lisp_Object** bvalues = (lisp_Object**) b->data;

    uintsize asize = LISP_OBJECT_GET_DATA(avalues[LISP_IDX_VECTOR_SIZE], uintsize);
    uintsize bsize = LISP_OBJECT_GET_DATA(bvalues[LISP_IDX_VECTOR_SIZE], uintsize);

    if (asize == 0) {
        return b;
    } else if (bsize == 0) {
        return a;
    } else {
        lisp_Object* new_vector = lisp_Vector_new_type(state, a->type);

        uintsize i = 0, il = asize;
        for (; i < il; i++) {
            lisp_Vector_mut_push(state, new_vector, lisp_Vector_get(state, a, i));
        }
        i = 0, il = bsize;
        for (; i < il; i++) {
            lisp_Vector_mut_push(state, new_vector, lisp_Vector_get(state, b, i));
        }

        return new_vector;
    }
}
uintsize lisp_Vector_index_of(lisp_State* state, lisp_Object* vector, lisp_Object* value) {
    lisp_Object** values = (lisp_Object**) vector->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SIZE], uintsize);

    uintsize i = 0, il = size;
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
static lisp_Object* lisp_Vector_find_node(lisp_State* state, lisp_Object* vector, uintsize index) {
    lisp_Object** values = (lisp_Object**) vector->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SIZE], uintsize);

    if (index >= lisp_Vector_tail_off(size)) {
        return values[LISP_IDX_VECTOR_TAIL];
    } else {
        lisp_Object* node = values[LISP_IDX_VECTOR_ROOT];
        uintsize level = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SHIFT], uintsize);

        while (level > 0) {
            node = ((lisp_Object**) node->data)[(index >> level) & LISP_VECTOR_MASK];
            level = level - LISP_VECTOR_SHIFT;
        }

        return node;
    }
}
lisp_Object* lisp_Vector_get(lisp_State* state, lisp_Object* vector, uintsize index) {
    lisp_Object** values = (lisp_Object**) vector->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SIZE], uintsize);

    if (index < size) {
        return ((lisp_Object**) lisp_Vector_find_node(state, vector, index)->data)[index & LISP_VECTOR_MASK];
    } else {
        return state->nil;
    }
}

static lisp_Object* lisp_Vector_new_path_set(
    lisp_State* state, lisp_Object* node, uintsize size, uintsize index, lisp_Object* value, uintsize level
) {
    lisp_Object* new_node = lisp_VectorNode_clone(state, node, ((size - 1) >> level) & LISP_VECTOR_MASK);
    lisp_Object** new_node_values = (lisp_Object**) new_node->data;

    if (level == 0) {
        new_node_values[index & LISP_VECTOR_MASK] = value;
    } else {
        uintsize sub_index = (index >> level) & LISP_VECTOR_MASK;
        new_node_values[sub_index] = lisp_Vector_new_path_set(
            state, ((lisp_Object**) node->data)[sub_index], size, index, value, level - LISP_VECTOR_SHIFT
        );
    }

    return new_node;
}
lisp_Object* lisp_Vector_set(lisp_State* state, lisp_Object* vector, uintsize index, lisp_Object* value) {
    lisp_Object** values = (lisp_Object**) vector->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SIZE], uintsize);

    if (index < size) {
        if (index >= lisp_Vector_tail_off(size)) {
            lisp_Object* tail = values[LISP_IDX_VECTOR_TAIL];
            lisp_Object** tail_values = (lisp_Object**) tail->data;
            uintsize masked_index = index & LISP_VECTOR_MASK;

            if (lisp_Object_equal(state, tail_values[masked_index], value)) {
                return vector;
            } else {
                lisp_Object* new_vector = lisp_Vector_clone(state, vector);
                lisp_Object** new_vector_values = (lisp_Object**) new_vector->data;

                tail = lisp_VectorNode_clone(state, tail, (size + 1) & LISP_VECTOR_MASK);
                ((lisp_Object**) tail->data)[masked_index] = value;
                new_vector_values[LISP_IDX_VECTOR_TAIL] = tail;

                return new_vector;
            }
        } else if (lisp_Object_equal(state, lisp_Vector_get(state, vector, index), value)) {
            return vector;
        } else {
            lisp_Object* new_vector = lisp_Vector_clone(state, vector);
            lisp_Object** new_vector_values = (lisp_Object**) new_vector->data;
            lisp_Object* root = new_vector_values[LISP_IDX_VECTOR_ROOT];
            uintsize shift = LISP_OBJECT_GET_DATA(new_vector_values[LISP_IDX_VECTOR_SHIFT], uintsize);
            new_vector_values[LISP_IDX_VECTOR_ROOT] = lisp_Vector_new_path_set(state, root, size, index, value, shift);
            return new_vector;
        }
    } else {
        return vector;
    }
}
static void lisp_Vector_mut_set(lisp_State* state, lisp_Object* vector, uintsize index, lisp_Object* value) {
    lisp_Object* node = lisp_Vector_find_node(state, vector, index);

    if (node != state->nil) {
        ((lisp_Object**) node->data)[index & LISP_VECTOR_MASK] = value;
    }
}

static lisp_Object* lisp_Vector_new_path(lisp_State* state, lisp_Object* node, uintsize level) {
    if (level == 0) {
        return node;
    } else {
        lisp_Object* new_node = lisp_VectorNode_new(state);
        lisp_Object** new_node_values = (lisp_Object**) new_node->data;
        new_node_values[0] = lisp_Vector_new_path(state, node, level - LISP_VECTOR_SHIFT);
        return new_node;
    }
}
static lisp_Object* lisp_Vector_push_tail(
    lisp_State* state, lisp_Object* parent, lisp_Object* tail_object, uintsize size, uintsize level
) {
    uintsize sub_index = ((size - 1) >> level) & LISP_VECTOR_MASK;
    lisp_Object* new_node = lisp_VectorNode_new(state);
    lisp_Object* node_to_insert = state->nil;

    if (level == LISP_VECTOR_SHIFT) {
        node_to_insert = tail_object;
    } else {
        lisp_Object* child = ((lisp_Object**) parent->data)[sub_index];

        if (child == state->nil) {
            node_to_insert = lisp_Vector_new_path(state, tail_object, level - LISP_VECTOR_SHIFT);
        } else {
            node_to_insert = lisp_Vector_push_tail(state, child, tail_object, size, level - LISP_VECTOR_SHIFT);
        }
    }

    ((lisp_Object**) new_node->data)[sub_index] = node_to_insert;

    return new_node;
}
static void lisp_Vector_mut_push(lisp_State* state, lisp_Object* vector, lisp_Object* value) {
    lisp_Object** values = (lisp_Object**) vector->data;

    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SIZE], uintsize);
    uintsize shift = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SHIFT], uintsize);

    if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        lisp_Object* tail = values[LISP_IDX_VECTOR_TAIL];
        if (tail == state->nil) {
            tail = values[LISP_IDX_VECTOR_TAIL] = lisp_VectorNode_new(state);
        }
        ((lisp_Object**) tail->data)[size & LISP_VECTOR_MASK] = value;
    } else {
        lisp_Object* root = values[LISP_IDX_VECTOR_ROOT];

        lisp_Object* new_root = state->nil;
        uintsize new_shift = shift;

        if ((size >> LISP_VECTOR_SHIFT) > (1 << shift)) {
            new_root = lisp_VectorNode_new(state);
            lisp_Object** new_root_values = (lisp_Object**) new_root->data;
            new_root_values[0] = root;
            new_root_values[1] = lisp_Vector_new_path(state, values[LISP_IDX_VECTOR_TAIL], shift);
            new_shift += LISP_VECTOR_SHIFT;
        } else {
            new_root = lisp_Vector_push_tail(state, root, values[LISP_IDX_VECTOR_TAIL], size, shift);
        }

        lisp_Object* new_tail = lisp_VectorNode_new(state);
        ((lisp_Object**) new_tail->data)[0] = value;
        values[LISP_IDX_VECTOR_TAIL] = new_tail;
        values[LISP_IDX_VECTOR_ROOT] = new_root;
        values[LISP_IDX_VECTOR_SHIFT] = lisp_Number_new_UInt(state, new_shift);
    }

    values[LISP_IDX_VECTOR_SIZE] = lisp_Number_new_UInt(state, size + 1);
}
lisp_Object* lisp_Vector_push(lisp_State* state, lisp_Object* vector, lisp_Object* value) {
    lisp_Object** values = (lisp_Object**) vector->data;

    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SIZE], uintsize);
    lisp_Object* new_vector = lisp_Vector_clone(state, vector);
    lisp_Object** new_vector_values = (lisp_Object**) new_vector->data;

    if (new_vector_values[LISP_IDX_VECTOR_TAIL] == state->nil) {
        new_vector_values[LISP_IDX_VECTOR_TAIL] = lisp_VectorNode_new(state);
    } else if (size - lisp_Vector_tail_off(size) < LISP_VECTOR_SIZE) {
        new_vector_values[LISP_IDX_VECTOR_TAIL] = lisp_VectorNode_clone(state, values[LISP_IDX_VECTOR_TAIL], (size + 1) & LISP_VECTOR_MASK);
    }

    lisp_Vector_mut_push(state, new_vector, value);

    return new_vector;
}

static lisp_Object* lisp_Vector_pop_tail(lisp_State* state, lisp_Object* node, uintsize size, uintsize level) {
    uintsize sub_index = ((size - 1) >> level) & LISP_VECTOR_MASK;

    if (level > LISP_VECTOR_SHIFT) {
        lisp_Object* new_child_object = lisp_Vector_pop_tail(
            state, ((lisp_Object**) node->data)[sub_index], size, level - LISP_VECTOR_SHIFT
        );

        if (new_child_object == state->nil) {
            return state->nil;
        } else {
            lisp_Object* new_node = lisp_VectorNode_clone(state, node, sub_index);
            ((lisp_Object**) new_node->data)[sub_index] = new_child_object;
            return new_node;
        }
    } else if (sub_index == 0) {
        return state->nil;
    } else {
        return lisp_VectorNode_clone(state, node, sub_index);
    }
}
lisp_Object* lisp_Vector_pop(lisp_State* state, lisp_Object* vector) {
    lisp_Object** values = (lisp_Object**) vector->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SIZE], uintsize);

    if (size == 0) {
        return vector;
    } else if (size == 1) {
        return lisp_Vector_new_type(state, vector->type);
    } else {
        lisp_Object* new_vector = lisp_Vector_new_type(state, vector->type);
        lisp_Object** new_vector_values = (lisp_Object**) new_vector->data;

        lisp_Object* new_root = state->nil;
        lisp_Object* new_tail = state->nil;
        uintsize new_shift;

        if ((size - lisp_Vector_tail_off(size)) > 1) {
            new_tail = lisp_VectorNode_clone(state, values[LISP_IDX_VECTOR_TAIL], (size - 1) & LISP_VECTOR_MASK);
            new_root = values[LISP_IDX_VECTOR_ROOT];
            new_shift = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SHIFT], uintsize);
        } else {
            new_tail = lisp_Vector_find_node(state, vector, size - 2);

            uintsize shift = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SHIFT], uintsize);
            new_root = lisp_Vector_pop_tail(state, values[LISP_IDX_VECTOR_ROOT], size, shift);
            new_shift = shift;

            if (new_root != state->nil) {
                lisp_Object** new_root_values = (lisp_Object**) new_root->data;

                if (shift > LISP_VECTOR_SHIFT && new_root_values[1] == state->nil) {
                    new_root = new_root_values[0];
                    new_shift -= LISP_VECTOR_SHIFT;
                }
            }
        }

        new_vector_values[LISP_IDX_VECTOR_ROOT] = new_root;
        new_vector_values[LISP_IDX_VECTOR_TAIL] = new_tail;
        new_vector_values[LISP_IDX_VECTOR_SIZE] = lisp_Number_new_UInt(state, size - 1);
        new_vector_values[LISP_IDX_VECTOR_SHIFT] = lisp_Number_new_UInt(state, new_shift);

        return new_vector;
    }
}

lisp_Object* lisp_Vector_unshift(lisp_State* state, lisp_Object* vector, lisp_Object* value) {
    lisp_Object** values = (lisp_Object**) vector->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SIZE], uintsize);

    if (size != 0) {
        lisp_GCHeader* gc_header = lisp_State_alloc(state, (size + 1) * sizeof(lisp_Object*));
        lisp_Object** array = (lisp_Object**) gc_header->data;

        uintsize i = 0, il = size, j = 1;
        for (; i < il; i++, j++) {
            array[j] = lisp_Vector_get(state, vector, i);
        }
        array[0] = value;

        lisp_Object* new_vector = lisp_Vector_new_type(state, vector->type);

        for (i = 0, il = size + 1; i < il; i++) {
            lisp_Vector_mut_push(state, new_vector, array[i]);
        }
        lisp_State_dealloc(state, gc_header);

        return new_vector;
    } else {
        return lisp_Vector_push(state, vector, value);
    }
}

lisp_Object* lisp_Vector_remove(lisp_State* state, lisp_Object* vector, uintsize index) {
    lisp_Object** values = (lisp_Object**) vector->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SIZE], uintsize);

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

        lisp_Object* new_vector = lisp_Vector_new_type(state, vector->type);

        for (i = 0, il = size - 1; i < il; i++) {
            lisp_Vector_mut_push(state, new_vector, array[i]);
        }
        lisp_State_dealloc(state, gc_header);

        return new_vector;
    } else {
        return vector;
    }
}
static void lisp_Vector_mut_remove(lisp_State* state, lisp_Object* vector, uintsize index) {
    lisp_Object** values = (lisp_Object**) vector->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_VECTOR_SIZE], uintsize);

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

        values[LISP_IDX_VECTOR_ROOT] = state->nil;
        values[LISP_IDX_VECTOR_TAIL] = state->nil;
        values[LISP_IDX_VECTOR_SIZE] = lisp_Number_new_UInt(state, 0);
        values[LISP_IDX_VECTOR_SHIFT] = lisp_Number_new_UInt(state, LISP_VECTOR_SHIFT);

        for (i = 0, il = size - 1; i < il; i++) {
            lisp_Vector_mut_push(state, vector, array[i]);
        }
        lisp_State_dealloc(state, gc_header);
    }
}

char* lisp_Vector_to_ascii(lisp_State* state, lisp_Object* vector) {
    if (vector->type != state->CharVector) {
        char* ascii = (char*) malloc(4 * sizeof(char));
        ascii[0] = 'n';
        ascii[1] = 'i';
        ascii[2] = 'l';
        ascii[3] = '\0';
        return ascii;
    } else {
        uintsize size = lisp_Vector_size(vector);
        char* ascii = (char*) malloc((size + 1) * sizeof(char));

        uintsize i = 0, il = size;
        for (; i < il; i++) {
            ascii[i] = LISP_OBJECT_GET_DATA(lisp_Vector_get(state, vector, i), char);
        }
        ascii[size] = '\0';

        return ascii;
    }
}


#endif
