#ifndef __LISP_LANG_FUNCTION_C__
#define __LISP_LANG_FUNCTION_C__


static lisp_Value* lisp_Function_call(lisp_State* state, lisp_Value* fn, lisp_Value* args, lisp_Scope* scope) {
    return NULL;
}

static void lisp_Function_boot(lisp_State* state) {
    /*
    lisp_Value* Function = state->Function;
    lisp_MutableMap* prototype = (lisp_MutableMap*) lisp_MutableList_get(state, (lisp_MutableList*) Function->values->data, LISP_IDX_TYPE_PROTOTYPE)->data;
    */
}


#endif
