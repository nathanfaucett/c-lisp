#ifndef __LISP_LANG_NIL_C__
#define __LISP_LANG_NIL_C__


inline static lisp_Value* lisp_Nil_to_string(lisp_State* state) {
    return lisp_Value_string(state, "nil");
}


#endif
