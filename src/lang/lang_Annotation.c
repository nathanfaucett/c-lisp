#ifndef __LISP_LANG_ANNOTATION_C__
#define __LISP_LANG_ANNOTATION_C__


lisp_Object* lisp_Annotation_new(lisp_State* state, lisp_Object* Type) {
    return lisp_Annotation_new_types(state, Type, state->nil);
}
lisp_Object* lisp_Annotation_new_types(lisp_State* state, lisp_Object* Type, lisp_Object* Types) {
    lisp_Object* object = lisp_boot_object_size(state, state->Symbol, 2 * sizeof(void*));
    lisp_Object** values = (lisp_Object**) object->data;
    values[LISP_IDX_ANNOTATION_TYPE] = Type;
    values[LISP_IDX_ANNOTATION_SUBTYPES] = Types;
    return object;
}


#endif
