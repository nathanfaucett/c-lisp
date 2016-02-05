#ifndef __LISP_LANG_OBJECT_H__
#define __LISP_LANG_OBJECT_H__


#define LISP_IDX_TYPE_NAME 0
#define LISP_IDX_TYPE_ATTRIBUTES 1
#define LISP_IDX_TYPE_TYPES 2
#define LISP_IDX_TYPE_SIZE 3
#define LISP_IDX_TYPE_SUPER 4
#define LISP_IDX_TYPE_PROTOTYPE 5
#define LISP_IDX_TYPE_TEMPLATE 6
#define LISP_IDX_TYPE_ABSTRACT 7
#define LISP_IDX_TYPE_BYTES 8
#define LISP_TYPE_SIZE 9


#define LISP_SET_DATA(object, type, value) \
    *((type*) object->data) = value
#define LISP_GET_DATA(object, type) \
    *((type*) object->data)


typedef struct lisp_Type {
    void (*alloc)(lisp_State*, struct lisp_Object*);
    void (*mark)(struct lisp_Object*);
} lisp_Type;


typedef struct lisp_Object {
    lisp_GCNode* gc_node;
    void* data;
    struct lisp_Object* values;
    struct lisp_Object* type;
} lisp_Object;


static lisp_Object* lisp_Object_alloc(lisp_State* state, lisp_Object* type);
static void lisp_Object_mark(lisp_Object* value);

static lisp_bool lisp_Object_inherits(lisp_State* state, lisp_Object* a, lisp_Object* b);

static lisp_Object* lisp_Object_call1(lisp_State* state, lisp_Object* object, lisp_Object* key, lisp_Object* a0, lisp_Object* scope);

static lisp_bool lisp_Object_equal(lisp_State* state, lisp_Object* a, lisp_Object* b);


#endif
