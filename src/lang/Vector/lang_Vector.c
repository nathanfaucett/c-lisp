#ifndef __LISP_LANG_VECTOR_C__
#define __LISP_LANG_VECTOR_C__


static lisp_Object* lisp_Vector_init(lisp_State* state, lisp_Object* vector) {
    lisp_Object** values = (lisp_Object**) vector->data;
    values[LISP_IDX_VECTOR_ROOT] = state->nil;
    values[LISP_IDX_VECTOR_TAIL] = state->nil;
    values[LISP_IDX_VECTOR_SIZE] = lisp_Number_new_UInt(state, 0);
    values[LISP_IDX_VECTOR_SHIFT] = lisp_Number_new_UInt(state, LISP_VECTOR_SHIFT);
    return vector;
}
static lisp_Object* lisp_Vector_new_type(lisp_State* state, lisp_Object* type) {
    lisp_Object* object = lisp_boot_object_size(state, type, sizeof(void*) * 4);
    return lisp_Vector_init(state, object);
}


#endif
