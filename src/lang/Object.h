#ifndef __LISP_LANG_OBJECT_H__
#define __LISP_LANG_OBJECT_H__


#define LISP_SET_DATA(object, type, value) \
    *((type*) object->data) = value
#define LISP_GET_DATA(object, type) \
    *((type*) object->data)


typedef struct lisp_Object {
    lisp_GCNode* gc_node;
    void* data;
    struct lisp_Object* values;
    struct lisp_Object* type;
} lisp_Object;


static lisp_Object* lisp_Object_alloc(lisp_State* state, lisp_Object* type);
static void lisp_Object_mark(lisp_Object* value);

static lisp_Object* lisp_Object_boot_alloc(lisp_State* state, lisp_Object* type);
static lisp_Object* lisp_Object_boot_init(lisp_Object* object, lisp_GCNode* gc_node, lisp_Object* type);
static lisp_Object* lisp_Object_boot_size(lisp_State* state, lisp_Object* type, lisp_size size);

static lisp_bool lisp_Object_inherits(lisp_State* state, lisp_Object* a, lisp_Object* b);

static lisp_Object* lisp_Object_call1(lisp_State* state, lisp_Object* object, lisp_Object* key, lisp_Object* a0, lisp_Object* scope);

static lisp_bool lisp_Object_equal(lisp_State* state, lisp_Object* a, lisp_Object* b);


#endif
