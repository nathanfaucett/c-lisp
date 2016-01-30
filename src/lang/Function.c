#ifndef __LISP_LANG_FUNCTION_C__
#define __LISP_LANG_FUNCTION_C__


static void lisp_Function_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Function* function = (lisp_Function*) value->data;
    function->name = NULL;
    function->dispatches = NULL;
    function->native = NULL;
}
static void lisp_Function_mark(lisp_Value* value) {
    lisp_Function* function = (lisp_Function*) value->data;

    if (function->name != NULL) {
        lisp_Value_mark(function->name);
    }
    if (function->dispatches != NULL) {
        lisp_Value_mark(function->dispatches);
    }
}

static lisp_Value* lisp_Function_call(lisp_State* state, lisp_Function* function, lisp_Value* args, lisp_Scope* scope) {
    if (function->native != NULL) {
        return function->native(state, args);
    } else {
        return args;
    }
}


#endif
