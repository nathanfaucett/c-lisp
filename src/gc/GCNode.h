#ifndef __LISP_GC_NODE_H__
#define __LISP_GC_NODE_H__


typedef struct lisp_GCNode {
    lisp_bool marked;
    lisp_usize bytes;
    void* object;
    struct lisp_GCNode* next;
    struct lisp_GCNodeData* root;
} lisp_GCNode;


static lisp_GCNode* lisp_GCNode_new(lisp_GCNode* next, lisp_usize bytes);
static void lisp_GCNode_delete(lisp_GCNode* gc_node);

static void* lisp_GCNode_assoc(struct lisp_GC* gc, lisp_GCNode* gc_node, lisp_usize bytes);
static void lisp_GCNode_dissoc(struct lisp_GC* gc, lisp_GCNode* gc_node, void* object);


#endif
