#ifndef __LISP_LANG_LIST_C__
#define __LISP_LANG_LIST_C__


static void lisp_List_alloc(lisp_State* state, lisp_Value* value) {
    lisp_List* list = (lisp_List*) value->data;
    list->self = value;
    list->root = NULL;
    list->tail = NULL;
    list->size = 0;
}
static void lisp_List_mark(lisp_Value* value) {
    lisp_List* list = (lisp_List*) value->data;

    if (list->root != NULL) {
        lisp_ListNode_mark(list->root);
    }
}

static lisp_Value* lisp_List_find_node(lisp_List* list, lisp_size index) {
    if (index == 0) {
        return list->root;
    } else if (index == list->size - 1) {
        return list->tail;
    } else if (index < list->size) {
        return lisp_ListNode_find_node(list->root, index);
    } else {
        return NULL;
    }
}
static lisp_size lisp_List_index_of(lisp_State* state, lisp_List* list, lisp_Value* key) {
    lisp_Value* value = list->root;
    lisp_ListNode* node = NULL;
    lisp_size index = 1;

    while (value != NULL) {
        node = (lisp_ListNode*) value->data;

        if (lisp_Value_equal(state, node->value, key)) {
            return index;
        }
        index += 1;
        value = node->next;
    }

    return 0;
}

static lisp_Value* lisp_List_get(lisp_State* state, lisp_List* list, lisp_size index) {
    lisp_Value* node = lisp_List_find_node(list, index);

    if (node != NULL) {
        return ((lisp_ListNode*) node->data)->value;
    } else {
        return state->nil;
    }
}
static lisp_Value* lisp_List_set(lisp_State* state, lisp_List* list, lisp_size index, lisp_Value* value) {
    if (index < list->size) {
        lisp_Value* node_value = lisp_List_find_node(list, index);
        lisp_ListNode* node = (lisp_ListNode*) node_value->data;

        if (lisp_Value_equal(state, node->value, value)) {
            return list->self;
        } else {
            lisp_Value* new_value = lisp_Value_alloc(state, state->List);
            lisp_List* new_list = (lisp_List*) new_value->data;

            lisp_Value* new_node_value = lisp_Value_alloc(state, state->ListNode);
            lisp_ListNode* new_node = (lisp_ListNode*) new_node_value->data;

            new_node->next = node->next;
            new_node->value = value;

            new_list->root = lisp_ListNode_copy_from_to(state, list->root, node_value, new_node_value);
            new_list->tail = node->next == NULL ? new_node_value : list->tail;
            new_list->size = list->size;

            return new_value;
        }
    } else {
        return list->self;
    }
}

static lisp_Value* lisp_List_push(lisp_State* state, lisp_List* list, lisp_Value* value) {
    lisp_Value* new_list_value = lisp_Value_alloc(state, state->List);
    lisp_List* new_list = (lisp_List*) new_list_value->data;

    lisp_Value* node_value = lisp_Value_alloc(state, state->ListNode);
    lisp_ListNode* node = (lisp_ListNode*) node_value->data;
    node->next = NULL;
    node->value = value;

    if (list->root != NULL) {
        new_list->root = lisp_ListNode_push(state, list->root, node_value);
        new_list->tail = node_value;
        new_list->size = list->size + 1;
    } else {
        new_list->root = node_value;
        new_list->tail = node_value;
        new_list->size = 1;
    }

    return new_list_value;
}

static lisp_Value* lisp_List_unshift(lisp_State* state, lisp_List* list, lisp_Value* value) {
    lisp_Value* new_list_value = lisp_Value_alloc(state, state->List);
    lisp_List* new_list = (lisp_List*) new_list_value->data;

    lisp_Value* node_value = lisp_Value_alloc(state, state->ListNode);
    lisp_ListNode* node = (lisp_ListNode*) node_value->data;
    node->value = value;

    if (list->root != NULL) {
        node->next = list->root;
        new_list->tail = list->tail;
        new_list->size = list->size + 1;
    } else {
        new_list->tail = node_value;
        new_list->size = 1;
    }

    new_list->root = node_value;

    return new_list_value;
}

static lisp_Value* lisp_List_pop(lisp_State* state, lisp_List* list) {
    if (list->size > 1) {
        lisp_Value* new_list_value = lisp_Value_alloc(state, state->List);
        lisp_List* new_list = (lisp_List*) new_list_value->data;

        lisp_Value* tail_value = list->tail;

        lisp_Value* root_value = list->root;
        lisp_ListNode* root = (lisp_ListNode*) root_value->data;

        lisp_Value* new_root_value = lisp_Value_alloc(state, state->ListNode);
        lisp_ListNode* new_root = (lisp_ListNode*) new_root_value->data;
        new_root->value = root->value;

        lisp_Value* new_tail_value = new_root_value;

        lisp_ListNode* new_tail = NULL;
        lisp_Value* tmp_value = NULL;
        lisp_ListNode* tmp = NULL;

        while (LISP_TRUE) {
            root_value = root->next;

            if (root_value == NULL || root_value == tail_value) {
                break;
            } else {
                root = (lisp_ListNode*) root_value->data;

                tmp_value = lisp_Value_alloc(state, state->ListNode);
                tmp = (lisp_ListNode*) tmp_value->data;

                tmp->value = root->value;

                new_tail = (lisp_ListNode*) new_tail_value->data;
                new_tail->next = tmp_value;

                new_tail_value = tmp_value;
            }
        }

        new_list->root = new_root_value;
        new_list->tail = new_tail_value;
        new_list->size = list->size - 1;

        return new_list_value;
    } else {
        return state->empty_list;
    }
}

static lisp_Value* lisp_List_shift(lisp_State* state, lisp_List* list) {
    if (list->size > 1) {
        lisp_Value* new_list_value = lisp_Value_alloc(state, state->List);
        lisp_List* new_list = (lisp_List*) new_list_value->data;

        new_list->root = ((lisp_ListNode*) list->root)->next;
        new_list->tail = list->tail;
        new_list->size = list->size - 1;

        return new_list_value;
    } else {
        return state->empty_list;
    }
}

static lisp_Value* lisp_List_remove(lisp_State* state, lisp_List* list, lisp_size index) {
    if (index == 0) {
        return lisp_List_shift(state, list);
    } else if (index == list->size - 1) {
        return lisp_List_pop(state, list);
    } else if (index < list->size) {
        lisp_Value* new_list_value = lisp_Value_alloc(state, state->List);
        lisp_List* new_list = (lisp_List*) new_list_value->data;

        lisp_Value* removed_node = lisp_ListNode_find_node(list->root, index);
        lisp_Value* new_root = lisp_ListNode_copy_from_to(state, list->root, removed_node, ((lisp_ListNode*) removed_node->data)->next);

        new_list->root = new_root;
        new_list->tail = list->tail;
        new_list->size = list->size - 1;

        return new_list_value;
    } else {
        return list->self;
    }
}

static lisp_bool lisp_List_equal(lisp_State* state, lisp_List* a, lisp_List* b) {
    if (a == b) {
        return LISP_TRUE;
    } else if (a->size != b->size) {
        return LISP_FALSE;
    } else {
        lisp_Value* anode_value = a->root;
        lisp_Value* bnode_value = b->root;
        lisp_ListNode* anode = NULL;
        lisp_ListNode* bnode = NULL;

        while (anode_value != NULL) {
            anode = (lisp_ListNode*) anode_value->data;
            bnode = (lisp_ListNode*) bnode_value->data;

            if (lisp_Value_equal(state, anode->value, bnode->value)) {
                anode_value = anode->next;
                bnode_value = bnode->next;
            } else {
                return LISP_FALSE;
            }
        }

        return LISP_TRUE;
    }
}


#endif
