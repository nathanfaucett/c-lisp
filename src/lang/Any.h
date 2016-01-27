#ifndef __LISP_LANG_ANY_H__
#define __LISP_LANG_ANY_H__


static lisp_Value* lisp_export_Any_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_export_Any_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static void lisp_Any_bootstrap(lisp_State* state);


#endif
