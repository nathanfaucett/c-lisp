#ifndef __LISP_LANG_MACRO_C__
#define __LISP_LANG_MACRO_C__


static lisp_Value* lisp_Macro_call(lisp_State* state, lisp_Value* macro, lisp_Value* args, lisp_Scope* scope) {
    return NULL;
}

static void lisp_Macro_boot(lisp_State* state) {
    /*
    lisp_Value* Macro = state->Macro;
    lisp_MutableMap* prototype = (lisp_MutableMap*) lisp_MutableList_get(state, (lisp_MutableList*) Macro->values->data, LISP_IDX_TYPE_PROTOTYPE)->data;
    */
}


#endif
