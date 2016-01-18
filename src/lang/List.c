#ifndef __LISP_LANG_LIST_C__
#define __LISP_LANG_LIST_C__


static lisp_ListNode* lisp_ListNode_constructor(lisp_ListNode* node, lisp_ListNode* next, lisp_Value* value) {
    node->ref_count = 1;
    node->next = next;
    node->value = value;
    return node;
}

static lisp_ListNode* lisp_ListNode_new(lisp_ListNode* next, lisp_Value* value) {
    return lisp_ListNode_constructor(
        (lisp_ListNode*) malloc(sizeof(lisp_ListNode)), next, value
    );
}

static void lisp_ListNode_delete(lisp_State* state, lisp_ListNode* node) {
    lisp_ListNode* next = node->next;

    if (next != NULL && next->ref_count == 0) {
        lisp_ListNode_delete(state, next);
    }

    lisp_Value_deref(state, node->value);
    free(node);
}

static void lisp_ListNode_ref(lisp_ListNode* node) {
    node->ref_count += 1;

    if (node->next != NULL) {
        lisp_ListNode_ref(node->next);
    }
}

static void lisp_ListNode_deref(lisp_State* state, lisp_ListNode* node) {
    node->ref_count -= 1;

    if (node->next != NULL) {
        lisp_ListNode_deref(state, node->next);
    }

    if (node->ref_count == 0) {
        lisp_ListNode_delete(state, node);
    }
}

static lisp_ListNode* lisp_ListNode_find_node(lisp_ListNode* node, lisp_u32 index) {
    lisp_u32 i = 0;

    while (node != NULL && i != index) {
        node = node->next;
        i += 1;
    }

    return node;
}


static lisp_List* lisp_List_constructor(lisp_List* list, lisp_ListNode* root, lisp_ListNode* tail, lisp_u32 size) {
    list->root = root;
    list->tail = tail;
    list->size = size;
    return list;
}

static void lisp_List_destructor(lisp_State* state, lisp_List* list) {
    if (list->root != NULL) {
        lisp_ListNode_deref(state, list->root);
    }
}

static lisp_Value* lisp_List_from_mut_list(lisp_State* state, lisp_MutList* mut_list) {
    lisp_u32 size = lisp_MutList_size(mut_list);

    if (size == 0) {
        return lisp_Value_list(state);
    } else {
        lisp_Value* list_value = lisp_List_internal_new(state);
        lisp_u32 i = size - 1;
        lisp_ListNode* tail = lisp_ListNode_new(NULL, lisp_MutList_get(mut_list, i));
        lisp_ListNode* root = tail;

        while (i--) {
            root = lisp_ListNode_new(root, lisp_MutList_get(mut_list, i));
        }
        lisp_List_constructor(&list_value->list, root, tail, size);

        return list_value;
    }
}

static lisp_Value* lisp_List_internal_new(lisp_State* state) {
    lisp_Value* value = lisp_State_alloc(state);
    value->type = LISP_TYPE_LIST;
    value->list.value = value;
    value->ref_count = 1;
    return value;
}

static lisp_u32 lisp_List_size(lisp_List* list) {
    return list->size;
}

static lisp_ListNode* lisp_List_find_node(lisp_List* list, lisp_u32 index) {
    if (index == 0) {
        return list->root;
    } else if (index == list->size - 1) {
        return list->tail;
    } else {
        return lisp_ListNode_find_node(list->root, index);
    }
}

static lisp_Value* lisp_List_get(lisp_State* state, lisp_List* list, lisp_u32 index) {
    lisp_ListNode* node = lisp_List_find_node(list, index);

    if (node != NULL) {
        return node->value;
    } else {
        return state->nil;
    }
}

static lisp_ListNode* lisp_ListNode_push(lisp_ListNode* node, lisp_ListNode* last) {
    if (node == NULL) {
        return last;
    } else {
        return lisp_ListNode_new(
            lisp_ListNode_push(node->next, last),
            node->value
        );
    }
}

static lisp_Value* lisp_List_push(lisp_State* state, lisp_List* list, lisp_Value* value) {
    lisp_Value* new_value = lisp_List_internal_new(state);
    lisp_ListNode* node = lisp_ListNode_new(NULL, value);

    lisp_Value_ref(value);

    if (list->root != NULL) {
        lisp_List_constructor(&new_value->list, lisp_ListNode_push(list->root, node), node, list->size + 1);
    } else {
        lisp_List_constructor(&new_value->list, node, node, 1);
    }

    return new_value;
}

static lisp_Value* lisp_List_unshift(lisp_State* state, lisp_List* list, lisp_Value* value) {
    lisp_Value* new_value = lisp_List_internal_new(state);
    lisp_ListNode* node = (lisp_ListNode*) malloc(sizeof(lisp_ListNode));

    lisp_Value_ref(value);

    if (list->root != NULL) {
        lisp_ListNode_constructor(node, list->root, value);
        lisp_ListNode_ref(list->root);
        lisp_List_constructor(&new_value->list, node, list->tail, list->size + 1);
    } else {
        lisp_ListNode_constructor(node, NULL, value);
        lisp_List_constructor(&new_value->list, node, node, 1);
    }

    return new_value;
}

static lisp_Value* lisp_List_pop(lisp_State* state, lisp_List* list) {
    if (list->size == 0) {
        return lisp_Value_list(state);
    } else if (list->size == 1) {
        return lisp_Value_list(state);
    } else {
        lisp_Value* new_value = lisp_List_internal_new(state);

        lisp_ListNode* root = list->root;
        lisp_ListNode* tail = list->tail;

        lisp_ListNode* new_root = lisp_ListNode_new(NULL, root->value);
        lisp_ListNode* new_tail = new_root;

        while (root != NULL && root != tail) {
            root = root->next;

            new_tail = lisp_ListNode_new(NULL, root->value);
            new_tail->next = new_tail;
        }

        lisp_List_constructor(&new_value->list, new_root, new_tail, list->size - 1);

        return new_value;
    }
}

static lisp_Value* lisp_List_shift(lisp_State* state, lisp_List* list) {
    if (list->size == 0) {
        return lisp_Value_list(state);
    } else if (list->size == 1) {
        return lisp_Value_list(state);
    } else {
        lisp_Value* new_value = lisp_List_internal_new(state);
        lisp_List_constructor(&new_value->list, list->root->next, list->tail, list->size - 1);
        return new_value;
    }
}

static struct lisp_Value* lisp_List_after(lisp_State* state, lisp_List* list, lisp_u32 index) {
    lisp_ListNode* node = lisp_List_find_node(list, index);

    if (node != NULL) {
        lisp_Value* new_value = lisp_List_internal_new(state);
        lisp_ListNode_ref(node);
        lisp_List_constructor(&new_value->list, node, list->tail, list->size);
        return new_value;
    } else {
        return lisp_Value_list(state);
    }
}

static lisp_ListNode* lisp_List_copy_from_to(lisp_ListNode* from, lisp_ListNode* to, lisp_ListNode* new_node) {
    if (from != to) {
        return lisp_ListNode_new(lisp_List_copy_from_to(from->next, to, new_node), from->value);
    } else {
        return new_node;
    }
}

static lisp_Value* lisp_List_remove_index(lisp_State* state, lisp_List* list, lisp_u32 index) {
    lisp_Value* new_value = lisp_List_internal_new(state);

    lisp_ListNode* removed_node = lisp_ListNode_find_node(list->root, index);
    lisp_ListNode* new_root = lisp_List_copy_from_to(list->root, removed_node, removed_node->next);
    lisp_List_constructor(&new_value->list, new_root, list->tail, list->size - 1);

    return new_value;
}

static lisp_Value* lisp_List_remove(lisp_State* state, lisp_List* list, lisp_Value* index) {
    if (index->type != LISP_TYPE_NUMBER) {
        return list->value;
    } else {
        lisp_u32 i = (lisp_u32) lisp_Number_get_i32(&index->number);

        if (i >= list->size) {
            return list->value;
        } else if (i == 0) {
            return lisp_List_shift(state, list);
        } else if (i == list->size - 1) {
            return lisp_List_pop(state, list);
        } else {
            return lisp_List_remove_index(state, list, i);
        }
    }
}

static lisp_Value* lisp_List_to_string(lisp_State* state, lisp_List* list) {
    lisp_Value* value = lisp_Value_string_from_cstring(state, "(");
    lisp_ListNode* node = list->root;

    while (node != NULL) {
        lisp_Value* value_to_string = lisp_Value_to_string(state, node->value);
        lisp_Value* tmp;
        node = node->next;

        if (node != NULL) {
            lisp_Value* separator = lisp_Value_string_from_cstring(state, " ");
            tmp = lisp_String_concat(state, &value_to_string->string, &separator->string);
            lisp_Value_deref(state, separator);
        } else {
            tmp = value_to_string;
        }

        lisp_Value* new_value = lisp_String_concat(state, &value->string, &tmp->string);
        lisp_Value_deref(state, value);
        lisp_Value_deref(state, tmp);

        value = new_value;
    }

    lisp_Value* end_bracket = lisp_Value_string_from_cstring(state, ")");
    lisp_Value* new_value = lisp_String_concat(state, &value->string, &end_bracket->string);
    lisp_Value_deref(state, end_bracket);
    lisp_Value_deref(state, value);

    return new_value;
}

static lisp_bool lisp_List_equal(lisp_List* a, lisp_List* b) {
    if (a->size != b->size) {
        return LISP_FALSE;
    } else {
        lisp_ListNode* anode = a->root;
        lisp_ListNode* bnode = b->root;

        while (anode != NULL) {
            if (!lisp_Value_equal(anode->value, bnode->value)) {
                return LISP_FALSE;
            }
            anode = anode->next;
            bnode = bnode->next;
        }

        return LISP_TRUE;
    }
}

#endif
