#ifndef __LISP_LANG_LIST_C__
#define __LISP_LANG_LIST_C__


static lisp_Object* lisp_List_init(lisp_State* state, lisp_Object* list) {
    lisp_Object** values = (lisp_Object**) list->data;
    values[LISP_IDX_LIST_ROOT] = state->nil;
    values[LISP_IDX_LIST_TAIL] = state->nil;
    values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, 0);
    return list;
}
static lisp_Object* lisp_List_new_type(lisp_State* state, lisp_Object* type) {
    lisp_Object* object = lisp_boot_object_size(state, type, sizeof(void*) * 3);
    return lisp_List_init(state, object);
}

uintsize lisp_List_size(lisp_Object* list) {
    return LISP_OBJECT_GET_DATA(((lisp_Object**) list->data)[LISP_IDX_LIST_SIZE], uintsize);
}

static lisp_Object* lisp_List_find_node(lisp_State* state, lisp_Object* list, uintsize index) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    if (index == 0) {
        return values[LISP_IDX_LIST_ROOT];
    } else if (index == size - 1) {
        return values[LISP_IDX_LIST_TAIL];
    } else if (index < size) {
        return lisp_ListNode_find_node(values[LISP_IDX_LIST_ROOT], index);
    } else {
        return state->nil;
    }
}
uintsize lisp_List_index_of(lisp_State* state, lisp_Object* list, lisp_Object* key) {
    lisp_Object** values = (lisp_Object**) list->data;
    lisp_Object* node = values[LISP_IDX_LIST_ROOT];
    uintsize index = 1;
    lisp_Object** node_values = NULL;

    while (node != state->nil) {
        node_values = (lisp_Object**) node->data;

        if (lisp_Object_equal(state, node_values[LISP_IDX_LIST_NODE_VALUE], key)) {
            return index;
        } else {
            index += 1;
            node = node_values[LISP_IDX_LIST_NODE_NEXT];
        }
    }

    return 0;
}

lisp_Object* lisp_List_concat(lisp_State* state, lisp_Object* a, lisp_Object* b) {
    lisp_Object** avalues = (lisp_Object**) a->data;
    lisp_Object** bvalues = (lisp_Object**) b->data;

    uintsize asize = LISP_OBJECT_GET_DATA(avalues[LISP_IDX_LIST_SIZE], uintsize);
    uintsize bsize = LISP_OBJECT_GET_DATA(bvalues[LISP_IDX_LIST_SIZE], uintsize);

    if (asize == 0) {
        return b;
    } else if (bsize == 0) {
        return a;
    } else {
        lisp_Object* new_list = lisp_List_new_type(state, a->type);
        lisp_Object** node_values = NULL;

        lisp_Object* node = avalues[LISP_IDX_LIST_ROOT];
        while (node != state->nil) {
            node_values = (lisp_Object**) node->data;
            lisp_List_mut_push(state, new_list, node_values[LISP_IDX_LIST_NODE_VALUE]);
            node = node_values[LISP_IDX_LIST_NODE_NEXT];
        }

        node = bvalues[LISP_IDX_LIST_ROOT];
        while (node != state->nil) {
            node_values = (lisp_Object**) node->data;
            lisp_List_mut_push(state, new_list, node_values[LISP_IDX_LIST_NODE_VALUE]);
            node = node_values[LISP_IDX_LIST_NODE_NEXT];
        }

        return new_list;
    }
}

static void lisp_List_mut_set_size(lisp_State* state, lisp_Object* list, uintsize size) {
    lisp_Object** values = (lisp_Object**) list->data;
    lisp_Object* tail = NULL;
    lisp_Object* node = NULL;

    uintsize i = 0, il = size;
    for (; i < il; i++) {
        node = lisp_ListNode_new(state, state->nil, state->nil);

        if (tail != state->nil) {
            ((lisp_Object**) tail->data)[LISP_IDX_LIST_NODE_NEXT] = node;
        } else {
            values[LISP_IDX_LIST_ROOT] = node;
        }
        tail = node;
    }

    values[LISP_IDX_LIST_TAIL] = tail;
    values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size);
}

lisp_Object* lisp_List_get(lisp_State* state, lisp_Object* list, uintsize index) {
    lisp_Object* node = lisp_List_find_node(state, list, index);

    if (node != state->nil) {
        return ((lisp_Object**) node->data)[LISP_IDX_LIST_NODE_VALUE];
    } else {
        return state->nil;
    }
}
lisp_Object* lisp_List_set(lisp_State* state, lisp_Object* list, uintsize index, lisp_Object* value) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    if (index < size) {
        lisp_Object* node = lisp_List_find_node(state, list, index);
        lisp_Object** node_values = (lisp_Object**) node->data;

        if (lisp_Object_equal(state, node_values[LISP_IDX_LIST_NODE_VALUE], value)) {
            return list;
        } else {
            lisp_Object* new_list = lisp_List_new_type(state, list->type);
            lisp_Object** new_list_values = (lisp_Object**) new_list->data;

            lisp_Object* new_node = lisp_ListNode_new(state, node_values[LISP_IDX_LIST_NODE_NEXT], value);

            new_list_values[LISP_IDX_LIST_ROOT] = lisp_ListNode_copy_from_to(state, values[LISP_IDX_LIST_ROOT], node, new_node);
            new_list_values[LISP_IDX_LIST_TAIL] = node_values[LISP_IDX_LIST_NODE_NEXT] == state->nil ? new_node : values[LISP_IDX_LIST_TAIL];
            new_list_values[LISP_IDX_LIST_SIZE] = values[LISP_IDX_LIST_SIZE];

            return new_list;
        }
    } else {
        return list;
    }
}
static void lisp_List_mut_set(lisp_State* state, lisp_Object* list, uintsize index, lisp_Object* value) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    if (index < size) {
        lisp_Object* node = lisp_List_find_node(state, list, index);
        ((lisp_Object**) node->data)[LISP_IDX_LIST_NODE_VALUE] = value;
    }
}

lisp_Object* lisp_List_push(lisp_State* state, lisp_Object* list, lisp_Object* value) {
    lisp_Object** values = (lisp_Object**) list->data;

    lisp_Object* new_list = lisp_List_new_type(state, list->type);
    lisp_Object** new_list_values = (lisp_Object**) new_list->data;

    lisp_Object* node = lisp_ListNode_new(state, state->nil, value);

    if (values[LISP_IDX_LIST_ROOT] != state->nil) {
        uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);
        new_list_values[LISP_IDX_LIST_ROOT] = lisp_ListNode_push(state, values[LISP_IDX_LIST_ROOT], node);
        new_list_values[LISP_IDX_LIST_TAIL] = node;
        new_list_values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size + 1);
    } else {
        new_list_values[LISP_IDX_LIST_ROOT] = node;
        new_list_values[LISP_IDX_LIST_TAIL] = node;
        new_list_values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, 1);
    }

    return new_list;
}
static void lisp_List_mut_push(lisp_State* state, lisp_Object* list, lisp_Object* value) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    lisp_Object* node = lisp_ListNode_new(state, state->nil, value);

    if (values[LISP_IDX_LIST_ROOT] != state->nil) {
        ((lisp_Object**) values[LISP_IDX_LIST_TAIL]->data)[LISP_IDX_LIST_NODE_NEXT] = node;
        values[LISP_IDX_LIST_TAIL] = node;
    } else {
        values[LISP_IDX_LIST_ROOT] = node;
        values[LISP_IDX_LIST_TAIL] = node;
    }

    values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size + 1);
}

lisp_Object* lisp_List_unshift(lisp_State* state, lisp_Object* list, lisp_Object* value) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    lisp_Object* new_list = lisp_List_new_type(state, list->type);
    lisp_Object** new_list_values = (lisp_Object**) new_list->data;

    lisp_Object* node = lisp_ListNode_new(state, values[LISP_IDX_LIST_ROOT], value);

    if (values[LISP_IDX_LIST_ROOT] != state->nil) {
        new_list_values[LISP_IDX_LIST_TAIL] = values[LISP_IDX_LIST_TAIL];
        new_list_values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size + 1);
    } else {
        new_list_values[LISP_IDX_LIST_TAIL] = node;
        new_list_values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size + 1);
    }

    new_list_values[LISP_IDX_LIST_ROOT] = node;

    return new_list;
}

lisp_Object* lisp_List_pop(lisp_State* state, lisp_Object* list) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    if (size > 1) {
        lisp_Object* new_list = lisp_List_new_type(state, list->type);
        lisp_Object** new_list_values = (lisp_Object**) new_list->data;

        lisp_Object* tail = values[LISP_IDX_LIST_TAIL];
        lisp_Object* root = values[LISP_IDX_LIST_ROOT];
        lisp_Object** root_values = (lisp_Object**) root->data;

        lisp_Object* new_root = lisp_ListNode_new(state, state->nil, root_values[LISP_IDX_LIST_NODE_VALUE]);
        lisp_Object* new_tail = new_root;
        lisp_Object* tmp = NULL;

        while (true) {
            root = root_values[LISP_IDX_LIST_NODE_NEXT];

            if (root == state->nil || root == tail) {
                break;
            } else {
                tmp = lisp_ListNode_new(state, state->nil, root_values[LISP_IDX_LIST_NODE_VALUE]);
                ((lisp_Object**) new_tail->data)[LISP_IDX_LIST_NODE_NEXT] = tmp;
                new_tail = tmp;
                root_values = (lisp_Object**) root->data;
            }
        }

        new_list_values[LISP_IDX_LIST_ROOT] = new_root;
        new_list_values[LISP_IDX_LIST_TAIL] = new_tail;
        new_list_values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size - 1);

        return new_list;
    } else {
        return lisp_List_new_type(state, list->type);
    }
}
lisp_Object* lisp_List_shift(lisp_State* state, lisp_Object* list) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    if (size > 1) {
        lisp_Object* new_list = lisp_List_new_type(state, list->type);
        lisp_Object** new_list_values = (lisp_Object**) new_list->data;

        new_list_values[LISP_IDX_LIST_ROOT] = ((lisp_Object**) values[LISP_IDX_LIST_ROOT])[LISP_IDX_LIST_NODE_NEXT];
        new_list_values[LISP_IDX_LIST_TAIL] = values[LISP_IDX_LIST_TAIL];
        new_list_values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size - 1);

        return new_list;
    } else {
        return lisp_List_new_type(state, list->type);
    }
}
lisp_Object* lisp_List_remove(lisp_State* state, lisp_Object* list, uintsize index) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    if (index == 0) {
        return lisp_List_shift(state, list);
    } else if (index == size - 1) {
        return lisp_List_pop(state, list);
    } else if (index < size) {
        lisp_Object* new_list = lisp_List_new_type(state, list->type);
        lisp_Object** new_list_values = (lisp_Object**) new_list->data;

        lisp_Object* removed_node = lisp_ListNode_find_node(values[LISP_IDX_LIST_ROOT], index);
        lisp_Object* new_root = lisp_ListNode_copy_from_to(state, values[LISP_IDX_LIST_ROOT], removed_node, ((lisp_Object**) removed_node->data)[LISP_IDX_LIST_NODE_NEXT]);

        new_list_values[LISP_IDX_LIST_ROOT] = new_root;
        new_list_values[LISP_IDX_LIST_TAIL] = values[LISP_IDX_LIST_TAIL];
        new_list_values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size - 1);

        return new_list;
    } else {
        return list;
    }
}

static void lisp_List_mut_pop(lisp_State* state, lisp_Object* list) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    if (size > 1) {
        values[LISP_IDX_LIST_TAIL] = lisp_List_find_node(state, list, size - 2);
        values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size - 1);
    } else if (size == 1) {
        values[LISP_IDX_LIST_ROOT] = state->nil;
        values[LISP_IDX_LIST_TAIL] = state->nil;
        values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, 0);
    }
}
static void lisp_List_mut_shift(lisp_State* state, lisp_Object* list) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    if (size > 1) {
        values[LISP_IDX_LIST_ROOT] = ((lisp_Object**) values[LISP_IDX_LIST_ROOT]->data)[LISP_IDX_LIST_NODE_NEXT];
        values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size + 1);
    } else if (size == 1) {
        values[LISP_IDX_LIST_ROOT] = state->nil;
        values[LISP_IDX_LIST_TAIL] = state->nil;
        values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, 0);
    }
}
static void lisp_List_mut_remove(lisp_State* state, lisp_Object* list, uintsize index) {
    lisp_Object** values = (lisp_Object**) list->data;
    uintsize size = LISP_OBJECT_GET_DATA(values[LISP_IDX_LIST_SIZE], uintsize);

    if (index == 0) {
        lisp_List_mut_shift(state, list);
    } else if (index == size - 1) {
        lisp_List_mut_pop(state, list);
    } else if (index < size) {
        lisp_Object* node = lisp_List_find_node(state, list, index - 1);
        lisp_Object** node_values = (lisp_Object**) node->data;
        node_values[LISP_IDX_LIST_NODE_NEXT] = ((lisp_Object**) node_values[LISP_IDX_LIST_NODE_NEXT]->data)[LISP_IDX_LIST_NODE_NEXT];
        values[LISP_IDX_LIST_SIZE] = lisp_Number_new_UInt(state, size - 1);
    }
}


#endif
