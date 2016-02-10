#ifndef __LISP_LANG_NUMBER_C__
#define __LISP_LANG_NUMBER_C__


static lisp_Object* lisp_Number_UInt(lisp_State* state, lisp_usize value) {
    lisp_Object* object = lisp_Object_alloc(state, state->UInt);
    LISP_SET_DATA(object, lisp_usize, value);
    return object;
}
static lisp_Object* lisp_Number_Int(lisp_State* state, lisp_isize value) {
    lisp_Object* object = lisp_Object_alloc(state, state->Int);
    LISP_SET_DATA(object, lisp_isize, value);
    return object;
}

static lisp_usize lisp_Number_get_UInt(lisp_State* state, lisp_Object* value) {
    if (lisp_Object_inherits(state, value->type, state->Number)) {
        lisp_Object* size_object = lisp_List_get(state, (lisp_List*) value->type->values->data, LISP_IDX_TYPE_SIZE);
        lisp_usize size = LISP_GET_DATA(size_object, lisp_usize);

        switch (size) {
            case 1:
                return LISP_GET_DATA(size_object, lisp_u8);
            case 2:
                return LISP_GET_DATA(size_object, lisp_u16);
            case 4:
                return LISP_GET_DATA(size_object, lisp_u32);
            default:
                return LISP_GET_DATA(size_object, lisp_u64);
        }
    } else {
        return 0;
    }
}


#endif
