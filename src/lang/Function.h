#ifndef __LISP_LANG_FUNCTION_H__
#define __LISP_LANG_FUNCTION_H__


typedef struct lisp_Function {
    struct lisp_Value* value;

    struct lisp_Value* name;
    struct lisp_Value* params;
    struct lisp_Value* body;

    struct lisp_Value* (*native)(lisp_State*, struct lisp_Value*, struct lisp_Scope*);
} lisp_Function;

static void lisp_Function_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Function_dealloc(lisp_State* state, lisp_Value* value);

static struct lisp_Value* lisp_Function_call(lisp_State* state, lisp_Function* fn, lisp_Value* arg_values, lisp_Scope* scope);


#endif
