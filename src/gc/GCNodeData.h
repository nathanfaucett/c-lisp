#ifndef __LISP_GC_NODE_DATA_H__
#define __LISP_GC_NODE_DATA_H__


typedef struct lisp_GCNodeData {
    struct lisp_GCNodeData* next;
    lisp_usize bytes;
    void* object;
} lisp_GCNodeData;


static lisp_GCNodeData* lisp_GCNodeData_new(lisp_GCNodeData* next, lisp_usize bytes);
static void lisp_GCNodeData_delete(lisp_GCNodeData* gc_node_data);


#endif
