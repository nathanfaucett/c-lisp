#ifndef __LISP_LANG_BOOL_C__
#define __LISP_LANG_BOOL_C__


static lisp_Object* lisp_Bool_new(lisp_State* state, lisp_bool value) {
    lisp_Object* object = lisp_Object_boot_size(state, state->Bool, 1);
    LISP_SET_DATA(object, lisp_bool, value);
    return object;
}


#endif
