#ifndef __LISP_LANG_INT64_H__
#define __LISP_LANG_INT64_H__


typedef struct lisp_Int64 {
    lisp_i64 value;
} lisp_Int64;

static void lisp_Int64_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Int64_dealloc(lisp_State* state, lisp_Value* value);


#endif
