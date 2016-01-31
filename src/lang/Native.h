#ifndef __LISP_LANG_NATIVE_H__
#define __LISP_LANG_NATIVE_H__


typedef struct lisp_Native {
    lisp_Value* name;
    lisp_Value* (*function)(lisp_State*, lisp_Value*, lisp_Scope* scope);
} lisp_Native;


static void lisp_Native_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Native_mark(lisp_Value* value);

static lisp_Value* lisp_Native_new(lisp_State* state, lisp_Value* name, lisp_Value* (*function)(lisp_State*, lisp_Value*, lisp_Scope* scope));

static lisp_Value* lisp_Native_call(lisp_State* state, lisp_Native* native, lisp_Value* args, lisp_Scope* scope);


#endif
