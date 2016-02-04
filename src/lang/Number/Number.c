#ifndef __LISP_LANG_NUMBER_C__
#define __LISP_LANG_NUMBER_C__


lisp_Value* lisp_Number_UInt(lisp_State* state, lisp_size integer) {
    lisp_Value* value = lisp_Value_alloc(state, state->UInt);
    LISP_SET_DATA(value, lisp_size, integer);
    return value;
}
lisp_size lisp_Number_get_size(lisp_State* state, lisp_Value* index) {
    if (lisp_Value_inherits(state, index->type, state->Number)) {
        lisp_Value* size_value = lisp_List_get(state, index->type->values->data, LISP_IDX_TYPE_SIZE);
        lisp_size size = LISP_GET_DATA(size_value, lisp_size);

        switch (size) {
            case 1:
                return LISP_GET_DATA(size_value, lisp_u8);
            case 2:
                return LISP_GET_DATA(size_value, lisp_u16);
            case 4:
                return LISP_GET_DATA(size_value, lisp_u32);
            default:
                return LISP_GET_DATA(size_value, lisp_u64);
        }
    } else {
        return 0;
    }
}


#endif
