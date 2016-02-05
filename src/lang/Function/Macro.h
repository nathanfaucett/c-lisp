#ifndef __LISP_LANG_MACRO_H__
#define __LISP_LANG_MACRO_H__


static lisp_Object* lisp_Macro_call(lisp_State* state, lisp_Object* macro, lisp_Object* args, lisp_Object* scope);

static void lisp_Macro_boot(lisp_State* state);


#endif
