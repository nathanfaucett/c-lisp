#ifndef __LISP_LANG_BOOL_H__
#define __LISP_LANG_BOOL_H__


typedef struct lisp_Bool {
    lisp_bool value;
} lisp_Bool;

static void lisp_Bool_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Bool_dealloc(lisp_State* state, lisp_Value* value);


#endif
