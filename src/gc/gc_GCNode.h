#ifndef __LISP_GC_GC_NODE_H__
#define __LISP_GC_GC_NODE_H__


typedef struct lisp_GCNode {
    struct lisp_GCNode* next;
    lisp_GCHeader* gc_header;
} lisp_GCNode;

static lisp_GCNode* lisp_GCNode_new(lisp_GCNode* next, lisp_GCHeader* gc_header);
static void lisp_GCNode_delete(lisp_GCNode* gc_node);


#endif
