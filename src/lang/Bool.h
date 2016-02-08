#ifndef __LISP_LANG_BOOL_H__
#define __LISP_LANG_BOOL_H__


static lisp_Object* lisp_Bool_new(lisp_State* state, lisp_bool value);

static lisp_Object* lisp_Bool_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope);
static lisp_Object* lisp_Bool_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope);

static void lisp_Bool_boot(lisp_State* state);


#endif
