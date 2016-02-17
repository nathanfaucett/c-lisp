#ifndef __LISP_LANG_OBJECT_C__
#define __LISP_LANG_OBJECT_C__


bool lisp_Object_mark(lisp_Object* object) {
    if (lisp_GCHeader_mark(object->gc_header)) {
        return true;
    } else {
        return false;
    }
}
bool lisp_Object_equal(lisp_State* state, lisp_Object* a, lisp_Object* b) {
    return a == b;
}

static lisp_Object* lisp_Object_boot_alloc(lisp_State* state, lisp_Object* type) {
    lisp_GCHeader* gc_header = lisp_State_alloc(state, sizeof(lisp_Object));
    lisp_Object* object = (lisp_Object*) gc_header->data;
    lisp_Object_boot_init(object, gc_header, type);
    return object;
}
static lisp_Object* lisp_Object_boot_init(lisp_Object* object, lisp_GCHeader* gc_header, lisp_Object* type) {
    object->gc_header = gc_header;
    object->data = NULL;
    object->type = type;
    return object;
}
static lisp_Object* lisp_Object_boot_size(lisp_State* state, lisp_Object* type, uintsize size) {
    lisp_Object* object = lisp_Object_boot_alloc(state, type);
    object->data = lisp_State_assoc(state, object->gc_header, size);
    return object;
}
static lisp_Object* lisp_Object_boot_template_size(lisp_State* state, lisp_Object* type, lisp_Object* template, uintsize size) {
    return lisp_Object_boot_size(state, type, size);
}


#endif
