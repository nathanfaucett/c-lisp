#ifndef __LISP_LANG_ARRAY_NODE_C__
#define __LISP_LANG_ARRAY_NODE_C__


static lisp_ArrayNode* lisp_ArrayNode_alloc(lisp_ArrayNode* next, lisp_Value* value) {
    lisp_ArrayNode* node = (lisp_ArrayNode*) malloc(sizeof(lisp_ArrayNode));
    node->next = next;
    node->value = value;
    return node;
}
static void lisp_ArrayNode_dealloc(lisp_ArrayNode* node) {
    if (node->next != NULL) {
        lisp_ArrayNode_dealloc(node->next);
    }
    free(node);
}
static void lisp_ArrayNode_mark(lisp_ArrayNode* node) {
    if (node->next != NULL) {
        lisp_ArrayNode_mark(node->next);
    }
    lisp_Value_mark(node->value);
}

static lisp_ArrayNode* lisp_ArrayNode_find_node(lisp_ArrayNode* node, lisp_size index) {
    lisp_size i = 0;

    while (node != NULL && i != index) {
        node = node->next;
        i += 1;
    }

    return node;
}


#endif
