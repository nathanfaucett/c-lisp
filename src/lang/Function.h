#ifndef __LISP_LANG_FUNCTION_H__
#define __LISP_LANG_FUNCTION_H__


typedef struct lisp_Function {
    lisp_Value* name;
    lisp_Value* dispatches;
    lisp_Value* (*native)(lisp_State*, lisp_Value*);
} lisp_Function;


static void lisp_Function_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Function_mark(lisp_Value* value);

static lisp_Value* lisp_Function_call(lisp_State* state, lisp_Function* function, lisp_Value* args, lisp_Scope* scope);


#endif
