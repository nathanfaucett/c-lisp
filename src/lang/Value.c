#ifndef __LISP_LANG_VALUE_C__
#define __LISP_LANG_VALUE_C__


static lisp_Value* lisp_Value_new(lisp_State* state, lisp_Value* type) {
    lisp_Value* value = lisp_State_alloc(state, sizeof(lisp_Value));
    value->ref_count = 1;
    value->type = type;
    value->value = NULL;
    value->values = NULL;
    if (type->value != NULL) {
        ((lisp_Type*) type->value)->alloc(state, value);
    }
    return value;

}
static void lisp_Value_delete(lisp_State* state, lisp_Value* value) {
    if (value->type != NULL) {
        ((lisp_Type*) ((lisp_Value*) value->type)->value)->dealloc(state, value);
    }
    lisp_State_dealloc(state, value);
}

lisp_Value* lisp_Value_ref(lisp_Value* value) {
    value->ref_count += 1;
    return value;
}
void lisp_Value_deref(lisp_State* state, lisp_Value* value) {
    value->ref_count -= 1;

    if (value->ref_count == 0) {
        lisp_Value_delete(state, value);
    }
}


#endif
