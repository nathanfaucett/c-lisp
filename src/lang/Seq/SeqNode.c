#ifndef __LISP_LANG_SEQ_NODE_C__
#define __LISP_LANG_SEQ_NODE_C__


static lisp_SeqNode* lisp_SeqNode_alloc(lisp_SeqNode* next, lisp_Value* value) {
    lisp_SeqNode* node = (lisp_SeqNode*) malloc(sizeof(lisp_SeqNode));
    node->next = next;
    node->value = value;
    return node;
}
static void lisp_SeqNode_dealloc(lisp_SeqNode* node) {
    if (node->next != NULL) {
        lisp_SeqNode_dealloc(node->next);
    }
    free(node);
}
static void lisp_SeqNode_mark(lisp_SeqNode* node) {
    if (node->next != NULL) {
        lisp_SeqNode_mark(node->next);
    }
    lisp_Value_mark(node->value);
}

static lisp_SeqNode* lisp_SeqNode_find_node(lisp_SeqNode* node, lisp_size index) {
    lisp_size i = 0;

    while (node != NULL && i != index) {
        node = node->next;
        i += 1;
    }

    return node;
}


#endif
