#ifndef __LISP_LANG_NIL_H__
#define __LISP_LANG_NIL_H__


static void lisp_Nil_alloc(lisp_State* state, struct lisp_Value* value);
static void lisp_Nil_dealloc(lisp_State* state, struct lisp_Value* value);

static struct lisp_Value* lisp_Nil_bootstrap(lisp_State* state);


#endif
