#ifndef __LISP_LANG_LIST_C__
#define __LISP_LANG_LIST_C__


inline static lisp_ListNode* lisp_ListNode_constructor(lisp_ListNode* node, lisp_ListNode* next, lisp_Value* value) {
    node->ref_count = 1;
    node->next = next;
    node->value = value;
    return node;
}

inline static void lisp_ListNode_destructor(lisp_State* state, lisp_ListNode* node) {
    lisp_Value_deref(state, node->value);
    free(node);
}

inline static lisp_ListNode* lisp_ListNode_new(lisp_ListNode* next, lisp_Value* value) {
    return lisp_ListNode_constructor(
        (lisp_ListNode*) malloc(sizeof(lisp_ListNode)), next, value
    );
}

inline static void lisp_ListNode_delete(lisp_State* state, lisp_ListNode* node) {
    lisp_ListNode* next = node->next;

    if (next != NULL && next->ref_count == 0) {
        lisp_ListNode_delete(state, next);
    }

    lisp_ListNode_destructor(state, node);
}

inline static void lisp_ListNode_ref(lisp_ListNode* node) {
    node->ref_count += 1;

    if (node->next != NULL) {
        lisp_ListNode_ref(node->next);
    }
}

inline static void lisp_ListNode_deref(lisp_State* state, lisp_ListNode* node) {
    node->ref_count -= 1;

    if (node->next != NULL) {
        lisp_ListNode_deref(state, node->next);
    }

    if (node->ref_count == 0) {
        lisp_ListNode_delete(state, node);
    }
}

inline static lisp_List* lisp_List_constructor(lisp_List* list, lisp_ListNode* root, lisp_ListNode* tail, lisp_u32 size) {
    list->root = root;
    list->tail = tail;
    list->size = size;
    return list;
}

inline static void lisp_List_destructor(lisp_State* state, lisp_List* list) {
    if (list->root != NULL) {
        lisp_ListNode_deref(state, list->root);
    }
}

inline static lisp_Value* lisp_List_internal_new(lisp_State* state) {
    lisp_Value* value = lisp_State_alloc(state);
    value->type = LISP_TYPE_LIST;
    value->list.value = value;
    value->ref_count = 1;
    return value;
}

inline static lisp_ListNode* lisp_List_find_node(lisp_List* list, lisp_u32 index) {
    if (index == 0) {
        return list->root;
    } else if (index == list->size - 1) {
        return list->tail;
    } else {
        lisp_ListNode* node = list->root;
        lisp_u32 i = 0;

        while (node != NULL && i != index) {
            node = node->next;
            i += 1;
        }

        return node;
    }
}

inline static lisp_Value* lisp_List_get_index(lisp_List* list, lisp_u32 index) {
    lisp_ListNode* node = lisp_List_find_node(list, index);

    if (node != NULL) {
        return node->value;
    } else {
        return NULL;
    }
}

inline static lisp_Value* lisp_List_get(lisp_State* state, lisp_List* list, lisp_Value* index) {
    lisp_Value* nil = state->nil;

    if (index->type != LISP_TYPE_NUMBER) {
        return nil;
    } else {
        lisp_Value* value = lisp_List_get_index(list, (lisp_u32) lisp_Number_get_i32(&index->number));

        if (value != NULL) {
            return value;
        } else {
            return nil;
        }
    }
}

inline static lisp_ListNode* lisp_ListNode_push(lisp_ListNode* node, lisp_ListNode* last) {
    if (node == NULL) {
        return last;
    } else {
        return lisp_ListNode_new(
            lisp_ListNode_push(node->next, last),
            node->value
        );
    }
}

inline static lisp_Value* lisp_List_push(lisp_State* state, lisp_List* list, lisp_Value* value) {
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

inline static lisp_Value* lisp_List_unshift(lisp_State* state, lisp_List* list, lisp_Value* value) {
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

inline static lisp_Value* lisp_List_pop(lisp_State* state, lisp_List* list) {
    if (list->size == 0) {
        return list->value;
    } else if (list->size == 1) {
        return state->empty_list;
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

inline static lisp_Value* lisp_List_shift(lisp_State* state, lisp_List* list) {
    if (list->size == 0) {
        return list->value;
    } else if (list->size == 1) {
        return state->empty_list;
    } else {
        lisp_Value* new_value = lisp_List_internal_new(state);
        lisp_List_constructor(&new_value->list, list->root->next, list->tail, list->size - 1);
        return new_value;
    }
}

inline static lisp_Value* lisp_List_to_string(lisp_State* state, lisp_List* list) {
    lisp_Value* new_value = NULL;
    lisp_Value* to_string = NULL;
    lisp_Value* value = lisp_Value_string_from_cstring(state, "(");
    lisp_ListNode* node = list->root;

    while (node != NULL) {
        to_string = lisp_Value_to_string(state, node->value);
        new_value = lisp_String_concat(state, &value->string, &to_string->string);

        lisp_Value_deref(state, to_string);
        lisp_Value_deref(state, value);

        value = new_value;
        node = node->next;
    }

    to_string = lisp_Value_string_from_cstring(state, ")");
    new_value = lisp_String_concat(state, &value->string, &to_string->string);

    lisp_Value_deref(state, to_string);
    lisp_Value_deref(state, value);

    return new_value;
}

#endif
