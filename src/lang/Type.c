#ifndef __LISP_LANG_TYPE_C__
#define __LISP_LANG_TYPE_C__


static void lisp_Type_boot(lisp_State* state) {
    lisp_Object* Type = state->Type;
    lisp_List* values = (lisp_List*) Type->values->data;

    lisp_List_mut_set(values, LISP_IDX_TYPE_NAME, lisp_String_from_ascii(state, "Type"));

    lisp_List* attributes = (lisp_List*) lisp_List_get(state, values, LISP_IDX_TYPE_ATTRIBUTES)->data;
    lisp_List_mut_set(attributes, LISP_IDX_TYPE_NAME, lisp_Symbol_from_ascii(state, "name"));
    lisp_List_mut_set(attributes, LISP_IDX_TYPE_ATTRIBUTES, lisp_Symbol_from_ascii(state, "attributes"));
    lisp_List_mut_set(attributes, LISP_IDX_TYPE_TYPES, lisp_Symbol_from_ascii(state, "types"));
    lisp_List_mut_set(attributes, LISP_IDX_TYPE_SIZE, lisp_Symbol_from_ascii(state, "size"));
    lisp_List_mut_set(attributes, LISP_IDX_TYPE_SUPER, lisp_Symbol_from_ascii(state, "super"));
    lisp_List_mut_set(attributes, LISP_IDX_TYPE_PROTOTYPE, lisp_Symbol_from_ascii(state, "prototype"));
    lisp_List_mut_set(attributes, LISP_IDX_TYPE_TEMPLATE, lisp_Symbol_from_ascii(state, "template"));
    lisp_List_mut_set(attributes, LISP_IDX_TYPE_ABSTRACT, lisp_Symbol_from_ascii(state, "abstract"));
    lisp_List_mut_set(attributes, LISP_IDX_TYPE_BYTES, lisp_Symbol_from_ascii(state, "bytes"));

    lisp_List* types = (lisp_List*) lisp_List_get(state, values, LISP_IDX_TYPE_TYPES)->data;
    lisp_List_mut_set(types, LISP_IDX_TYPE_NAME, lisp_Annotation_new(state, state->Symbol));
    lisp_List_mut_set(types, LISP_IDX_TYPE_ATTRIBUTES, lisp_Annotation_new(state, state->List));
    lisp_List_mut_set(types, LISP_IDX_TYPE_TYPES, lisp_Annotation_new(state, state->List));
    lisp_List_mut_set(types, LISP_IDX_TYPE_SIZE, lisp_Annotation_new(state, state->UInt));
    lisp_List_mut_set(types, LISP_IDX_TYPE_SUPER, lisp_Annotation_new(state, state->Type));
    lisp_List_mut_set(types, LISP_IDX_TYPE_PROTOTYPE, lisp_Annotation_new(state, state->Map));
    lisp_List_mut_set(types, LISP_IDX_TYPE_TEMPLATE, lisp_Annotation_new(state, state->Map));
    lisp_List_mut_set(types, LISP_IDX_TYPE_ABSTRACT, lisp_Annotation_new(state, state->Bool));
    lisp_List_mut_set(types, LISP_IDX_TYPE_BYTES, lisp_Annotation_new(state, state->Bool));
}


#endif
