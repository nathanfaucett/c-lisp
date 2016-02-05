#ifndef __LISP_LANG_NATIVE_H__
#define __LISP_LANG_NATIVE_H__


static lisp_Object* lisp_Native_new(lisp_State* state, lisp_Object* (*fn)(lisp_State*, lisp_Object*, lisp_Object*));

static lisp_Object* lisp_Native_call(lisp_State* state, lisp_Object* native, lisp_Object* args, lisp_Object* scope);

static lisp_Object* lisp_Native_export_call(lisp_State* state, lisp_Object* args, lisp_Object* scope);
static lisp_Object* lisp_Native_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope);
static lisp_Object* lisp_Native_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope);

static void lisp_Native_boot(lisp_State* state);


#endif
