#ifndef __LISP_LANG_NIL_C__
#define __LISP_LANG_NIL_C__


static lisp_Value* lisp_Nil_to_string(lisp_State* state) {
    return lisp_Value_string_from_cstring(state, "nil");
}

static lisp_bool lisp_Nil_equal(lisp_Nil* a, lisp_Nil* b) {
    return LISP_TRUE;
}


#endif
