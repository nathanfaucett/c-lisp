#ifndef __LISP_GC_GC_NODE_C__
#define __LISP_GC_GC_NODE_C__


static lisp_GCNode* lisp_GCNode_new(lisp_GCNode* next,  lisp_GCHeader* gc_header) {
    lisp_GCNode* gc_node = (lisp_GCNode*) malloc(sizeof(lisp_GCNode));
    gc_node->next = next;
    gc_node->gc_header = gc_header;
    return gc_node;
}
static void lisp_GCNode_delete(lisp_GCNode* gc_node) {
    if (gc_node->next != NULL) {
        lisp_GCNode_delete(gc_node->next);
    }
    lisp_GCHeader_delete(gc_node->gc_header);
    free(gc_node);
}


#endif
