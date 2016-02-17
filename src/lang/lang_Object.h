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


bool lisp_Object_mark(lisp_Object* object);
bool lisp_Object_equal(lisp_State* state, lisp_Object* a, lisp_Object* b);

static lisp_Object* lisp_Object_boot_alloc(lisp_State* state, lisp_Object* type);
static lisp_Object* lisp_Object_boot_init(lisp_Object* object, lisp_GCHeader* gc_header, lisp_Object* type);
static lisp_Object* lisp_Object_boot_size(lisp_State* state, lisp_Object* type, uintsize size);
static lisp_Object* lisp_Object_boot_template_size(lisp_State* state, lisp_Object* type, lisp_Object* template, uintsize size);


#endif
