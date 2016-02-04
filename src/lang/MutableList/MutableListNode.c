#ifndef __LISP_LANG_MUTABLE_LIST_NODE_C__
#define __LISP_LANG_MUTABLE_LIST_NODE_C__


static lisp_MutableListNode* lisp_MutableListNode_alloc(lisp_MutableListNode* next, lisp_Value* value) {
    lisp_MutableListNode* node = (lisp_MutableListNode*) malloc(sizeof(lisp_MutableListNode));
    node->next = next;
    node->value = value;
    return node;
}
static void lisp_MutableListNode_dealloc(lisp_MutableListNode* node) {
    if (node->next != NULL) {
        lisp_MutableListNode_dealloc(node->next);
    }
    free(node);
}
static void lisp_MutableListNode_mark(lisp_MutableListNode* node) {
    if (node->next != NULL) {
        lisp_MutableListNode_mark(node->next);
    }
    lisp_Value_mark(node->value);
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
