#ifndef __LISP_GC_GC_HEADER_NODE_C__
#define __LISP_GC_GC_HEADER_NODE_C__


static lisp_GCHeaderNode* lisp_GCHeaderNode_new(lisp_GCHeaderNode* next,  lisp_GCData* gc_data) {
    lisp_GCHeaderNode* gc_header_node = (lisp_GCHeaderNode*) malloc(sizeof(lisp_GCHeaderNode));
    gc_header_node->next = next;
    gc_header_node->gc_data = gc_data;
    return gc_header_node;
}
static void lisp_GCHeaderNode_delete(lisp_GCHeaderNode* gc_header_node) {
    if (gc_header_node->next != NULL) {
        lisp_GCHeaderNode_delete(gc_header_node->next);
    }
    lisp_GCData_delete(gc_header_node->gc_data);
    free(gc_header_node);
}


#endif
