#ifndef __LISP_LANG_INT64_C__
#define __LISP_LANG_INT64_C__


static void lisp_Int64_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Int64* int64 = (lisp_Int64*) lisp_State_alloc(state, sizeof(lisp_Int64));
    value->value = int64;
    int64->value = 0;
}
static void lisp_Int64_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_State_dealloc(state, value->value);
}


#endif
