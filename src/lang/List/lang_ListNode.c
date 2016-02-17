#ifndef __LISP_LANG_LIST_NODE_C__
#define __LISP_LANG_LIST_NODE_C__


static void lisp_ListNode_mark(lisp_ListNode* node) {
    if (lisp_GCHeader_mark(node->gc_header)) {
        if (node->next != NULL) {
            lisp_ListNode_mark(node->next);
        }
        lisp_Object_mark(node->value);
    }
}

static lisp_ListNode* lisp_ListNode_new(lisp_State* state, lisp_ListNode* next, lisp_Object* value) {
    lisp_GCHeader* gc_header = lisp_State_alloc(state, sizeof(lisp_ListNode));
    lisp_ListNode* node = (lisp_ListNode*) gc_header->data;
    node->gc_header = gc_header;
    node->next = next;
    node->value = value;
    return node;
}

static lisp_ListNode* lisp_ListNode_find_node(lisp_ListNode* node, uintsize index) {
    uintsize i = 0;

    while (node != NULL && i != index) {
        node = node->next;
        i += 1;
    }

    return node;
}
static lisp_ListNode* lisp_ListNode_copy_from_to(lisp_State* state, lisp_ListNode* from, lisp_ListNode* to, lisp_ListNode* new_node) {
    if (from != to) {
        return lisp_ListNode_new(
            state,
            lisp_ListNode_copy_from_to(state, from->next, to, new_node),
            from->value
        );
    } else {
        return new_node;
    }
}
static lisp_ListNode* lisp_ListNode_push(lisp_State* state, lisp_ListNode* node, lisp_ListNode* last_node) {
    if (node != NULL) {
        return lisp_ListNode_new(
            state,
            lisp_ListNode_push(state, node->next, last_node),
            node->value
        );
    } else {
        return last_node;
    }
}


#endif
