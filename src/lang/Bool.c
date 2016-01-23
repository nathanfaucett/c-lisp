#ifndef __LISP_LANG_BOOL_C__
#define __LISP_LANG_BOOL_C__


static void lisp_Bool_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Bool* bool = (lisp_Bool*) lisp_State_alloc(state, sizeof(lisp_Bool));
    value->value = bool;
    bool->value = LISP_TRUE;
}
static void lisp_Bool_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_State_dealloc(state, value->value);
}


#endif
