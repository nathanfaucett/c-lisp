#ifndef __LISP_BOOT_SPECIAL_FORMS_LIB_H__
#define __LISP_BOOT_SPECIAL_FORMS_LIB_H__


static lisp_Value* lisp_boot_special_forms_def(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_swap(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_if(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_do(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_let(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_quote(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_fn(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_macro(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_type(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static lisp_Value* lisp_boot_special_forms_try(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_catch(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_finally(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_boot_special_forms_throw(lisp_State* state, lisp_Value* args, lisp_Scope* scope);


#endif
