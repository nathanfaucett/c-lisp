#ifndef __LISP_LANG_LIST_C__
#define __LISP_LANG_LIST_C__


inline static lisp_ListNode* lisp_ListNode_new(lisp_ListNode* node, lisp_ListNode* next, lisp_Value* value) {
    node->ref_count = 0;
    node->next = next;
    node->value = value;
    return node;
}

inline static void lisp_ListNode_delete(lisp_State* state, lisp_ListNode* node) {
    if (node->ref_count == 0) {
        lisp_ListNode* next = node->next;

        if (next != NULL) {
            lisp_ListNode_delete(state, next);
        }

        lisp_Value_deref(state, node->value);
        free(node);
    }
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


inline static lisp_List* lisp_List_new(lisp_List* list, lisp_ListNode* root, lisp_ListNode* tail, lisp_u32 size) {
    list->root = root;
    list->tail = tail;
    list->size = size;
    return list;
}

inline static void lisp_List_delete(lisp_State* state, lisp_List* list) {
    if (list->root != NULL) {
        lisp_ListNode_deref(state, list->root);
    }
}

inline static lisp_ListNode* lisp_List_find_node(lisp_List* list, lisp_u32 index) {
    lisp_ListNode* node = list->root;
    lisp_u32 i = 0;

    while (node != NULL && i != index) {
        node = node->next;
        i += 1;
    }

    return node;
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
        lisp_Value* value = lisp_List_get_index(list, (lisp_u32) index->number.float_value);

        if (value != NULL) {
            return value;
        } else {
            return nil;
        }
    }
}

inline static lisp_Value* lisp_List_unshift(lisp_State* state, lisp_List* list, lisp_Value* value) {
    lisp_Value* new_value = lisp_Value_list(state);
    lisp_ListNode* node = (lisp_ListNode*) malloc(sizeof(lisp_ListNode));

    lisp_Value_ref(value);

    if (list->root != NULL) {
        lisp_ListNode_new(node, list->root, value);
        lisp_ListNode_ref(node);
        lisp_List_new(&new_value->list, node, list->tail, list->size + 1);
    } else {
        lisp_ListNode_new(node, NULL, value);
        lisp_ListNode_ref(node);
        lisp_List_new(&new_value->list, node, node, 1);
    }

    return new_value;
}

inline static lisp_u8* lisp_List_to_cstring(lisp_List* list) {
    return str_clone("(List)");
}

#endif
