#ifndef __LISP_LANG_FUNCTION_H__
#define __LISP_LANG_FUNCTION_H__


static lisp_Value* lisp_Function_call(lisp_State* state, lisp_Value* fn, lisp_Value* args, lisp_Scope* scope);

static void lisp_Function_boot(lisp_State* state);


#endif
