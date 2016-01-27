#ifndef __LISP_LANG_NIL_H__
#define __LISP_LANG_NIL_H__


static lisp_Value* lisp_export_Nil_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_export_Nil_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static void lisp_Nil_bootstrap(lisp_State* state);


#endif
