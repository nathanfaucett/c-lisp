#ifndef __LISP_LANG_ANNOTATION_C__
#define __LISP_LANG_ANNOTATION_C__


static lisp_Object* lisp_Annotation_new(lisp_State* state, lisp_Object* Type) {
    return lisp_Annotation_new_template(state, Type, state->nil);
}
static lisp_Object* lisp_Annotation_new_template(lisp_State* state, lisp_Object* Type, lisp_Object* template) {
    lisp_Object* object = lisp_Object_boot_alloc(state, state->Annotation);
    lisp_Object* values_object = lisp_Vector_new(state);

    lisp_Vector* values = (lisp_Vector*) values_object->data;
    lisp_Vector_mut_push(state, values, Type);
    lisp_Vector_mut_push(state, values, template);
    object->values = values_object;

    return object;
}


#endif
