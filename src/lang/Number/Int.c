#ifndef __LISP_LANG_INT_C__
#define __LISP_LANG_INT_C__


static lisp_u64 lisp_Int_to_u64(lisp_State* state, lisp_Value* value) {
    lisp_Type* type = (lisp_Type*) value->type->value;

    if (type == (lisp_Type*) state->type_int64->value) {
        return ((lisp_Int64*) value->value)->value;
    } else {
        return 0;
    }
}


#endif
