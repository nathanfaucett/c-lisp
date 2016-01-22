#ifndef __LISP_LANG_ANY_H__
#define __LISP_LANG_ANY_H__


static void lisp_Any_alloc(lisp_State* state, struct lisp_Value* value);
static void lisp_Any_dealloc(lisp_State* state, struct lisp_Value* value);

static struct lisp_Value* lisp_Any_bootstrap(lisp_State* state);


#endif
