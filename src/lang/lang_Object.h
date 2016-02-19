#ifndef __LISP_LANG_OBJECT_H__
#define __LISP_LANG_OBJECT_H__


#define LISP_OBJECT_SET_DATA(object, type, value) \
    *((type*) object->data) = value
#define LISP_OBJECT_GET_DATA(object, type) \
    *((type*) object->data)


typedef struct lisp_Object {
    lisp_GCHeader* gc_header;
    struct lisp_Object* type;
    void* data;
} lisp_Object;

static lisp_Object* lisp_Object_alloc(lisp_State* state, lisp_Object* type);

bool lisp_Object_mark(lisp_Object* object);
bool lisp_Object_equal(lisp_State* state, lisp_Object* a, lisp_Object* b);


#endif
