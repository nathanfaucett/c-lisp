#ifndef __LISP_LANG_NIL_H__
#define __LISP_LANG_NIL_H__


static lisp_Object* lisp_Nil_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope);
static lisp_Object* lisp_Nil_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope);

static void lisp_Nil_boot(lisp_State* state);


#endif
