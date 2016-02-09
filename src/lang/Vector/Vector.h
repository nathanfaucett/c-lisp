#ifndef __LISP_LANG_VECTOR_H__
#define __LISP_LANG_VECTOR_H__


typedef struct lisp_Vector {
    lisp_Object* self;
    lisp_Object* root;
    lisp_Object* tail;
    lisp_size size;
    lisp_size shift;
} lisp_Vector;


static void lisp_Vector_alloc(lisp_State* state, lisp_Object* object);
static void lisp_Vector_mark(lisp_Object* object);

static lisp_Object* lisp_Vector_new(lisp_State* state);

static lisp_size lisp_Vector_tail_off(lisp_size size);
static lisp_Object* lisp_Vector_find_node(lisp_Vector* vector, lisp_size size);
static lisp_Object* lisp_Vector_get(lisp_State* state, lisp_Vector* vector, lisp_size index);

static lisp_Object* lisp_Vector_new_path_set(
    lisp_State* state, lisp_Object* node_object, lisp_size size, lisp_size index, lisp_Object* value, lisp_size level
);
static lisp_Object* lisp_Vector_set(lisp_State* state, lisp_Vector* vector, lisp_size index, lisp_Object* value);

static lisp_Object* lisp_Vector_new_path(lisp_State* state, lisp_Object* node_object, lisp_size level);
static lisp_Object* lisp_Vector_push_tail(
    lisp_State* state, lisp_Object* parent_object, tail_object, lisp_size size, lisp_size level
);
static lisp_Object* lisp_Vector_mut_push(lisp_State* state, lisp_Vector* vector, lisp_Object* value);
static lisp_Object* lisp_Vector_push(lisp_State* state, lisp_Vector* vector, lisp_Object* value);

#endif
