#ifndef __LISP_LANG_BOOLEAN_C__
#define __LISP_LANG_BOOLEAN_C__


static lisp_Boolean* lisp_Boolean_constructor(lisp_Boolean* boolean, lisp_bool value) {
    boolean->boolean_value = value;
    return boolean;
}

static lisp_Value* lisp_Boolean_to_string(lisp_State* state, lisp_Boolean* boolean) {
    if (boolean->boolean_value == LISP_TRUE) {
        return lisp_Value_string_from_cstring(state, "true");
    } else {
        return lisp_Value_string_from_cstring(state, "false");
    }
}

static lisp_bool lisp_Boolean_equal(lisp_Boolean* a, lisp_Boolean* b) {
    return a->boolean_value == b->boolean_value;
}


#endif
