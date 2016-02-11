#ifndef __LISP_LANG_TYPE_C__
#define __LISP_LANG_TYPE_C__


static void lisp_Type_boot(lisp_State* state) {
    lisp_Object* Type = state->Type;
    lisp_Vector* values = (lisp_Vector*) Type->values->data;

    lisp_Vector_mut_set(values, LISP_IDX_TYPE_NAME, lisp_String_from_ascii(state, "Type"));

    lisp_Vector* attributes = (lisp_Vector*) lisp_Vector_get(state, values, LISP_IDX_TYPE_ATTRIBUTES)->data;
    lisp_Vector_mut_set(attributes, LISP_IDX_TYPE_NAME, lisp_Symbol_from_ascii(state, "name"));
    lisp_Vector_mut_set(attributes, LISP_IDX_TYPE_ATTRIBUTES, lisp_Symbol_from_ascii(state, "attributes"));
    lisp_Vector_mut_set(attributes, LISP_IDX_TYPE_TYPES, lisp_Symbol_from_ascii(state, "types"));
    lisp_Vector_mut_set(attributes, LISP_IDX_TYPE_SIZE, lisp_Symbol_from_ascii(state, "size"));
    lisp_Vector_mut_set(attributes, LISP_IDX_TYPE_SUPER, lisp_Symbol_from_ascii(state, "super"));
    lisp_Vector_mut_set(attributes, LISP_IDX_TYPE_PROTOTYPE, lisp_Symbol_from_ascii(state, "prototype"));
    lisp_Vector_mut_set(attributes, LISP_IDX_TYPE_TEMPLATE, lisp_Symbol_from_ascii(state, "template"));
    lisp_Vector_mut_set(attributes, LISP_IDX_TYPE_ABSTRACT, lisp_Symbol_from_ascii(state, "abstract"));
    lisp_Vector_mut_set(attributes, LISP_IDX_TYPE_BYTES, lisp_Symbol_from_ascii(state, "bytes"));

    lisp_Vector* types = (lisp_Vector*) lisp_Vector_get(state, values, LISP_IDX_TYPE_TYPES)->data;
    lisp_Vector_mut_set(types, LISP_IDX_TYPE_NAME, lisp_Annotation_new(state, state->Symbol));
    lisp_Vector_mut_set(types, LISP_IDX_TYPE_ATTRIBUTES, lisp_Annotation_new(state, state->Vector));
    lisp_Vector_mut_set(types, LISP_IDX_TYPE_TYPES, lisp_Annotation_new(state, state->Vector));
    lisp_Vector_mut_set(types, LISP_IDX_TYPE_SIZE, lisp_Annotation_new(state, state->UInt));
    lisp_Vector_mut_set(types, LISP_IDX_TYPE_SUPER, lisp_Annotation_new(state, state->Type));
    lisp_Vector_mut_set(types, LISP_IDX_TYPE_PROTOTYPE, lisp_Annotation_new(state, state->Map));
    lisp_Vector_mut_set(types, LISP_IDX_TYPE_TEMPLATE, lisp_Annotation_new(state, state->Map));
    lisp_Vector_mut_set(types, LISP_IDX_TYPE_ABSTRACT, lisp_Annotation_new(state, state->Bool));
    lisp_Vector_mut_set(types, LISP_IDX_TYPE_BYTES, lisp_Annotation_new(state, state->Bool));
}


#endif
