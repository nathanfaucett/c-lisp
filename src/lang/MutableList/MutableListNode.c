#ifndef __LISP_LANG_MUTABLE_LIST_NODE_C__
#define __LISP_LANG_MUTABLE_LIST_NODE_C__


static lisp_MutableListNode* lisp_MutableListNode_alloc(lisp_State* state, lisp_GCNode* gc_node, lisp_MutableListNode* next, lisp_Object* object) {
    lisp_MutableListNode* node = (lisp_MutableListNode*) lisp_State_assoc(state, gc_node, sizeof(lisp_MutableListNode));
    node->next = next;
    node->object = object;
    return node;
}
static void lisp_MutableListNode_dealloc(lisp_State* state, lisp_GCNode* gc_node, lisp_MutableListNode* node) {
    if (node->next != NULL) {
        lisp_MutableListNode_dealloc(state, gc_node, node->next);
    }
    lisp_State_dissoc(state, gc_node, node);
}
static void lisp_MutableListNode_mark(lisp_MutableListNode* node) {
    if (node->next != NULL) {
        lisp_MutableListNode_mark(node->next);
    }
    lisp_Object_mark(node->object);
}

static lisp_MutableListNode* lisp_MutableListNode_find_node(lisp_MutableListNode* node, lisp_size index) {
    lisp_size i = 0;

    while (node != NULL && i != index) {
        node = node->next;
        i += 1;
    }

    return node;
}


#endif
