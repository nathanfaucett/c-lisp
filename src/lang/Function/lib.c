#ifndef __LISP_LANG_FUNCTION_LIB_C__
#define __LISP_LANG_FUNCTION_LIB_C__


#include "./Function.c"
#include "./Macro.c"
#include "./Native.c"


static lisp_Object* lisp_function_call(lisp_State* state, lisp_Object* fn, lisp_Object* args, lisp_Object* scope) {
    if (fn->type == state->Function) {
        return lisp_Function_call(state, fn, args, scope);
    } else if (fn->type == state->Macro) {
        return lisp_Macro_call(state, fn, args, scope);
    } else if (fn->type == state->Native) {
        return lisp_Native_call(state, fn, args, scope);
    } else {
        return lisp_Object_call1(state, fn, lisp_Symbol_from_ascii(state, "call"), args, scope);
    }
}


#endif
