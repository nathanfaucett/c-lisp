#ifndef __LISP_LANG_VECTOR_NODE_H__
#define __LISP_LANG_VECTOR_NODE_H__


typedef struct lisp_VectorNode {
    lisp_Object** array;
} lisp_VectorNode;

static void lisp_VectorNode_alloc(lisp_State* state, lisp_Object* object);
static void lisp_VectorNode_mark(lisp_Object* object);

static lisp_Object* lisp_VectorNode_new(lisp_State* state);

static lisp_Object* lisp_VectorNode_clone(lisp_State* state, lisp_Object* node_object, lisp_size length);


#endif
