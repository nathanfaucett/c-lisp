#ifndef __LISP_LANG_FUNCTION_H__
#define __LISP_LANG_FUNCTION_H__


static lisp_Object* lisp_Function_call(lisp_State* state, lisp_Object* fn, lisp_Object* args, lisp_Object* scope);

static void lisp_Function_boot(lisp_State* state);


#endif
