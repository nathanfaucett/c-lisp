#ifndef __LISP_LANG_MUTABLE_LIST_NODE_C__
#define __LISP_LANG_MUTABLE_LIST_NODE_C__


static lisp_ListNode* lisp_ListNode_alloc(lisp_State* state, lisp_GCNode* gc_node, lisp_ListNode* next, lisp_Object* object) {
    lisp_ListNode* node = (lisp_ListNode*) lisp_State_assoc(state, gc_node, sizeof(lisp_ListNode));
    node->next = next;
    node->object = object;
    return node;
}
static void lisp_ListNode_dealloc(lisp_State* state, lisp_GCNode* gc_node, lisp_ListNode* node) {
    if (node->next != NULL) {
        lisp_ListNode_dealloc(state, gc_node, node->next);
    }
    lisp_State_dissoc(state, gc_node, node);
}
static void lisp_ListNode_mark(lisp_ListNode* node) {
    if (node->next != NULL) {
        lisp_ListNode_mark(node->next);
    }
    lisp_Object_mark(node->object);
}

static lisp_ListNode* lisp_ListNode_find_node(lisp_ListNode* node, lisp_size index) {
    lisp_size i = 0;

    while (node != NULL && i != index) {
        node = node->next;
        i += 1;
    }

    return node;
}


#endif
