#ifndef __LISP_LANG_BOOL_H__
#define __LISP_LANG_BOOL_H__


typedef struct lisp_Bool {
    lisp_bool value;
} lisp_Bool;

static void lisp_Bool_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Bool_dealloc(lisp_State* state, lisp_Value* value);

static lisp_Value* lisp_export_Bool_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_export_Bool_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static void lisp_Bool_bootstrap(lisp_State* state);


#endif
