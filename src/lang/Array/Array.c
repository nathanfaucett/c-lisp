#ifndef __LISP_LANG_ARRAY_C__
#define __LISP_LANG_ARRAY_C__


static void lisp_Array_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Array* array = (lisp_Array*) value->data;
    array->root = NULL;
    array->tail = NULL;
    array->size = 0;
}
static void lisp_Array_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Array* array = (lisp_Array*) value->data;

    if (array->root != NULL) {
        lisp_ArrayNode_dealloc(array->root);
    }
}
static void lisp_Array_mark(lisp_Value* value) {
    lisp_Array* array = (lisp_Array*) value->data;

    if (array->root != NULL) {
        lisp_ArrayNode_mark(array->root);
    }
}

static lisp_ArrayNode* lisp_Array_find_node(lisp_Array* array, lisp_size index) {
    if (index == 0) {
        return array->root;
    } else if (index == array->size - 1) {
        return array->tail;
    } else if (index < array->size) {
        return lisp_ArrayNode_find_node(array->root, index);
    } else {
        return NULL;
    }
}

static lisp_size lisp_Array_index_of(lisp_State* state, lisp_Array* array, lisp_Value* key) {
    lisp_ArrayNode* node = array->root;
    lisp_size index = 1;

    while (node != NULL) {
        if (lisp_Value_equal(state, node->value, key)) {
            return index;
        }
        index += 1;
        node = node->next;
    }

    return 0;
}

static lisp_Value* lisp_Array_get(lisp_State* state, lisp_Array* array, lisp_size index) {
    lisp_ArrayNode* node = lisp_Array_find_node(array, index);

    if (node != NULL) {
        return node->value;
    } else {
        return state->nil;
    }
}
static void lisp_Array_set(lisp_Array* array, lisp_size index, lisp_Value* value) {
    lisp_ArrayNode* node = lisp_Array_find_node(array, index);

    if (node != NULL) {
        node->value = value;
    }
}

static void lisp_Array_set_size(lisp_State* state, lisp_Array* array, lisp_size new_size) {
    if (new_size == 0) {
        if (array->root != NULL) {
            lisp_ArrayNode_dealloc(array->root);
        }
        array->root = NULL;
        array->tail = NULL;
    } else if (new_size < array->size) {
        lisp_ArrayNode* node = lisp_Array_find_node(array, new_size - 1);

        if (node->next != NULL) {
            lisp_ArrayNode_dealloc(node->next);
        }
    } else if (new_size > array->size) {
        lisp_ArrayNode* tail = array->tail;
        lisp_ArrayNode* node = NULL;

        lisp_size i = array->size, il = new_size;
        for (; i < il; i++) {
            node = lisp_ArrayNode_alloc(NULL, state->nil);
            if (tail != NULL) {
                tail->next = node;
            } else {
                array->root = node;
            }
            tail = node;
        }

        array->tail = tail;
    }
    array->size = new_size;
}

static void lisp_Array_push(lisp_Array* array, lisp_Value* value) {
    lisp_ArrayNode* node = lisp_ArrayNode_alloc(NULL, value);

    if (array->root != NULL) {
        array->tail->next = node;
        array->tail = node;
    } else {
        array->root = node;
        array->tail = node;
    }

    array->size += 1;
}

static void lisp_Array_unshift(lisp_Array* array, lisp_Value* value) {
    lisp_ArrayNode* node = lisp_ArrayNode_alloc(array->root, value);

    if (array->root != NULL) {
        array->root = node;
    } else {
        array->root = node;
        array->tail = node;
    }

    array->size += 1;
}

static void lisp_Array_pop(lisp_Array* array) {
    if (array->size > 1) {
        lisp_ArrayNode* tail = array->tail;

        array->tail = lisp_Array_find_node(array, array->size - 2);
        lisp_ArrayNode_dealloc(tail);

        array->size -= 1;
    } else if (array->size == 1) {
        lisp_ArrayNode_dealloc(array->tail);
        array->root = NULL;
        array->tail = NULL;
        array->size = 0;
    }
}

static void lisp_Array_shift(lisp_Array* array) {
    if (array->size > 1) {
        lisp_ArrayNode* root = array->root;

        array->root = root->next;
        lisp_ArrayNode_dealloc(root);

        array->size -= 1;
    } else if (array->size == 1) {
        lisp_ArrayNode_dealloc(array->root);
        array->root = NULL;
        array->tail = NULL;
        array->size = 0;
    }
}

static void lisp_Array_remove(lisp_Array* array, lisp_size index) {
    if (index == 0) {
        lisp_Array_shift(array);
    } else if (index == array->size - 1) {
        lisp_Array_pop(array);
    } else if (index < array->size) {
        lisp_ArrayNode* node = lisp_Array_find_node(array, index - 1);
        lisp_ArrayNode* removed_node = node->next;

        node->next = removed_node->next;
        removed_node->next = NULL;

        lisp_ArrayNode_dealloc(removed_node);

        array->size -= 1;
    }
}

static lisp_bool lisp_Array_equal(lisp_State* state, lisp_Array* a, lisp_Array* b) {
    if (a == b) {
        return LISP_TRUE;
    } else if (a->size != b->size) {
        return LISP_FALSE;
    } else {
        lisp_ArrayNode* anode = a->root;
        lisp_ArrayNode* bnode = b->root;

        while (anode != NULL) {
            if (lisp_Value_equal(state, anode->value, bnode->value)) {
                anode = anode->next;
                bnode = bnode->next;
            } else {
                return LISP_FALSE;
            }
        }

        return LISP_TRUE;
    }
}

static void lisp_Array_boot(lisp_State* state) {

}


#endif
