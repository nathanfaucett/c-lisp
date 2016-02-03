#ifndef __LISP_LANG_NATIVE_H__
#define __LISP_LANG_NATIVE_H__


static lisp_Value* lisp_Native_new(lisp_State* state, lisp_Value* (*fn)(lisp_State*, lisp_Value*, lisp_Scope*));

static lisp_Value* lisp_Native_call(lisp_State* state, lisp_Value* native, lisp_Value* args, lisp_Scope* scope);

static lisp_Value* lisp_Native_export_call(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_Native_export_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_Native_export_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static void lisp_Native_boot(lisp_State* state);


#endif
