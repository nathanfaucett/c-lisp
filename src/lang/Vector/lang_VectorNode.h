#ifndef __LISP_LANG_VECTOR_NODE_H__
#define __LISP_LANG_VECTOR_NODE_H__


static lisp_Object* lisp_VectorNode_new(lisp_State* state);

static lisp_Object* lisp_VectorNode_clone(lisp_State* state, lisp_Object* node_object, uintsize length);


#endif
