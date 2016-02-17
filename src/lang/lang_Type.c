#ifndef __LISP_LANG_TYPE_C__
#define __LISP_LANG_TYPE_C__


static void lisp_Type_alloc(lisp_State* state, lisp_Object* object) {
    lisp_Type* type = (lisp_Type*) object->data;
    type->name = NULL;
    type->attributes = NULL;
    type->types = NULL;
    type->super = NULL;
    type->prototype = NULL;
    type->template = NULL;
    type->abstract = false;
    type->bytes = false;
    type->size = 0;
    type->subtypes = NULL;
    type->alloc = lisp_Type_alloc;
    type->mark = lisp_Type_mark;
}
static void lisp_Type_mark(lisp_Object* object) {
    lisp_Type* type = (lisp_Type*) object->data;

    if (type->name != NULL) { lisp_Object_mark(type->name); }
    if (type->attributes != NULL) { lisp_Object_mark(type->attributes); }
    if (type->types != NULL) { lisp_Object_mark(type->types); }
    if (type->super != NULL) { lisp_Object_mark(type->super); }
    if (type->subtypes != NULL) { lisp_Object_mark(type->subtypes); }
}


#endif
