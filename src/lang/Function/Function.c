#ifndef __LISP_LANG_FUNCTION_C__
#define __LISP_LANG_FUNCTION_C__


static lisp_Object* lisp_Function_call(lisp_State* state, lisp_Object* fn, lisp_Object* args, lisp_Object* scope) {
    return NULL;
}

static void lisp_Function_boot(lisp_State* state) {
    /*
    lisp_Object* Function = state->Function;
    lisp_MutableMap* prototype = (lisp_MutableMap*) lisp_MutableList_get(state, (lisp_MutableList*) Function->values->data, LISP_IDX_TYPE_PROTOTYPE)->data;
    */
}


#endif
