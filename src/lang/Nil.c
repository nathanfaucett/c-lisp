#ifndef __LISP_LANG_NIL_C__
#define __LISP_LANG_NIL_C__


static void lisp_Nil_alloc(lisp_State* state, lisp_Value* value) {
    value->value = NULL;
}
static void lisp_Nil_dealloc(lisp_State* state, lisp_Value* value) {
    /* nothing to do but don't call the default function */
}

static lisp_Value* lisp_Nil_bootstrap(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_Nil_alloc,
        lisp_Nil_dealloc
    );
    return value;
}


#endif
