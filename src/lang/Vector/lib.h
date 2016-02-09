#ifndef __LISP_LANG_VECTOR_LIB_H__
#define __LISP_LANG_VECTOR_LIB_H__


#define LISP_VECTOR_SHIFT 5
#define LISP_VECTOR_SIZE (1 << LISP_VECTOR_SHIFT)
#define LISP_VECTOR_MASK (LISP_VECTOR_SIZE - 1)


#include "./VectorNode.h"
#include "./Vector.h"


#endif
