#ifndef __LISP_LANG_ARRAY_H__
#define __LISP_LANG_ARRAY_H__


typedef struct lisp_Array {
    lisp_Object* self;
    lisp_Object** objects;
    lisp_usize size;
} lisp_Array;


static void lisp_Array_alloc(lisp_State* state, lisp_Object* object);
static void lisp_Array_mark(lisp_Object* object);

static lisp_Object* lisp_Array_new(lisp_State* state);

static void lisp_Array_set_size(lisp_State* state, lisp_Array* array, lisp_usize size);

static lisp_Object* lisp_Array_get(lisp_State* state, lisp_Array* array, lisp_usize index);
static void lisp_Array_set(lisp_Array* array, lisp_usize index, lisp_Object* value);

static lisp_bool lisp_Array_equal(lisp_State* state, lisp_Array* a, lisp_Array* b);


#endif
