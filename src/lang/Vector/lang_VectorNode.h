#ifndef __LISP_LANG_VECTOR_NODE_H__
#define __LISP_LANG_VECTOR_NODE_H__


typedef struct lisp_VectorNode {
    lisp_GCHeader* gc_header;
    struct lisp_VectorNode** nodes;
    lisp_Object** values;
} lisp_VectorNode;

static void lisp_VectorNode_mark(lisp_VectorNode* node);

static lisp_VectorNode* lisp_VectorNode_new_nodes(lisp_State* state);
static lisp_VectorNode* lisp_VectorNode_new_values(lisp_State* state);

static lisp_VectorNode* lisp_VectorNode_clone(lisp_State* state, lisp_VectorNode* node, uintsize length);


#endif
