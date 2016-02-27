#ifndef __LISP_LANG_TYPE_C__
#define __LISP_LANG_TYPE_C__


static void lisp_Type_boot(lisp_State* state, lisp_Object* Type) {
    lisp_Object** values = (lisp_Object**) Type->data;

    lisp_Object* attributes = values[LISP_IDX_TYPE_ATTRIBUTES];
    lisp_Vector_mut_set_size(state, attributes, LISP_TYPE_SIZE);

    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_NAME, lisp_Vector_from_ascii(state, "name"));
    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_ATTRIBUTES, lisp_Vector_from_ascii(state, "attributes"));
    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_TYPES, lisp_Vector_from_ascii(state, "types"));
    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_SIZE, lisp_Vector_from_ascii(state, "size"));
    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_SUPER, lisp_Vector_from_ascii(state, "super"));
    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_PROTOTYPE, lisp_Vector_from_ascii(state, "prototype"));
    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_TEMPLATE, lisp_Vector_from_ascii(state, "template"));
    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_ABSTRACT, lisp_Vector_from_ascii(state, "abstract"));
    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_BYTES, lisp_Vector_from_ascii(state, "bytes"));
    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_IMMUTABLE, lisp_Vector_from_ascii(state, "immutable"));
    lisp_Vector_mut_set(state, attributes, LISP_IDX_TYPE_SUBTYPES, lisp_Vector_from_ascii(state, "subtypes"));

    lisp_Object* types = values[LISP_IDX_TYPE_TYPES];
    lisp_Vector_mut_set_size(state, types, LISP_TYPE_SIZE);

    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_NAME, lisp_Annotation_new(state, state->Vector));
    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_ATTRIBUTES, lisp_Annotation_new(state, state->Vector));
    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_TYPES, lisp_Annotation_new(state, state->Vector));
    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_SIZE, lisp_Annotation_new(state, state->UInt));
    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_SUPER, lisp_Annotation_new(state, state->Type));
    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_PROTOTYPE, lisp_Annotation_new(state, state->Map));
    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_TEMPLATE, lisp_Annotation_new(state, state->Map));
    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_ABSTRACT, lisp_Annotation_new(state, state->Bool));
    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_BYTES, lisp_Annotation_new(state, state->Bool));
    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_IMMUTABLE, lisp_Annotation_new(state, state->Bool));
    lisp_Vector_mut_set(state, types, LISP_IDX_TYPE_SUBTYPES, lisp_Annotation_new(state, state->Map));
}


#endif
