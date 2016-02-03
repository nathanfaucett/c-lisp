#ifndef __LISP_LANG_MACRO_H__
#define __LISP_LANG_MACRO_H__


static lisp_Value* lisp_Macro_call(lisp_State* state, lisp_Value* macro, lisp_Value* args, lisp_Scope* scope);

static void lisp_Macro_boot(lisp_State* state);


#endif
