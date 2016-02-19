#ifndef __LISP_LANG_VECTOR_H__
#define __LISP_LANG_VECTOR_H__


#define LISP_VECTOR_SHIFT 5
#define LISP_VECTOR_SIZE (1 << LISP_VECTOR_SHIFT)
#define LISP_VECTOR_MASK (LISP_VECTOR_SIZE - 1)

#define LISP_IDX_VECTOR_ROOT 0
#define LISP_IDX_VECTOR_TAIL 1
#define LISP_IDX_VECTOR_SIZE 2
#define LISP_IDX_VECTOR_SHIFT 3


static lisp_Object* lisp_Vector_init(lisp_State* state, lisp_Object* map);
static lisp_Object* lisp_Vector_new_type(lisp_State* state, lisp_Object* type);


#endif
