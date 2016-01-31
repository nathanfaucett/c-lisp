#ifndef __LISP_LANG_MACRO_C__
#define __LISP_LANG_MACRO_C__


static void lisp_Macro_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Macro* macro = (lisp_Macro*) value->data;
    macro->name = NULL;
    macro->dispatches = NULL;
}
static void lisp_Macro_mark(lisp_Value* value) {
    lisp_Macro* macro = (lisp_Macro*) value->data;

    if (macro->name != NULL) {
        lisp_Value_mark(macro->name);
    }
    if (macro->dispatches != NULL) {
        lisp_Value_mark(macro->dispatches);
    }
}

static lisp_Value* lisp_Macro_call(lisp_State* state, lisp_Macro* macro, lisp_Value* args, lisp_Scope* scope) {
    return args;
}


#endif
