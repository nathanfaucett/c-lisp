#ifndef __LISP_LANG_NUMBERS_C__
#define __LISP_LANG_NUMBERS_C__


lisp_Object* lisp_Number_new_Int(lisp_State* state, intsize value) {
    lisp_Object* object = lisp_boot_object_size(state, state->Int, sizeof(intsize));
    LISP_OBJECT_SET_DATA(object, intsize, value);
    return object;
}
lisp_Object* lisp_Number_new_UInt(lisp_State* state, uintsize value) {
    lisp_Object* object = lisp_boot_object_size(state, state->UInt, sizeof(intsize));
    LISP_OBJECT_SET_DATA(object, uintsize, value);
    return object;
}


#endif
