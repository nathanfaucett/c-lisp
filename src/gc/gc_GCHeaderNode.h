#ifndef __LISP_GC_GC_HEADER_NODE_H__
#define __LISP_GC_GC_HEADER_NODE_H__


typedef struct lisp_GCHeaderNode {
    struct lisp_GCHeaderNode* next;
    lisp_GCData* gc_data;
} lisp_GCHeaderNode;

static lisp_GCHeaderNode* lisp_GCHeaderNode_new(lisp_GCHeaderNode* next, lisp_GCData* gc_data);
static void lisp_GCHeaderNode_delete(lisp_GCHeaderNode* gc_header_node);


#endif
