#ifndef __LISP_LANG_NUMBER_C__
#define __LISP_LANG_NUMBER_C__


lisp_Object* lisp_Number_UInt(lisp_State* state, lisp_size integer) {
    lisp_Object* object = lisp_Object_alloc(state, state->UInt);
    LISP_SET_DATA(object, lisp_size, integer);
    return object;
}
lisp_size lisp_Number_get_UInt(lisp_State* state, lisp_Object* index) {
    if (lisp_Object_inherits(state, index->type, state->Number)) {
        lisp_Object* size_object = lisp_List_get(state, (lisp_List*) index->type->values->data, LISP_IDX_TYPE_SIZE);
        lisp_size size = LISP_GET_DATA(size_object, lisp_size);

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
