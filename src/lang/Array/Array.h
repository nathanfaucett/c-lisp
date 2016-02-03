#ifndef __LISP_LANG_ARRAY_H__
#define __LISP_LANG_ARRAY_H__


typedef struct lisp_Array {
    lisp_ArrayNode* root;
    lisp_ArrayNode* tail;
    lisp_size size;
} lisp_Array;


static void lisp_Array_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Array_dealloc(lisp_State* state, lisp_Value* value);
static void lisp_Array_mark(lisp_Value* value);

static lisp_size lisp_Array_index_of(lisp_State* state, lisp_Array* array, lisp_Value* key);

static lisp_Value* lisp_Array_get(lisp_State* state, lisp_Array* array, lisp_size index);
static void lisp_Array_set(lisp_Array* array, lisp_size index, lisp_Value* value);

static void lisp_Array_set_size(lisp_State* state, lisp_Array* array, lisp_size new_size);

static void lisp_Array_push(lisp_Array* array, lisp_Value* value);
static void lisp_Array_unshift(lisp_Array* array, lisp_Value* value);

static void lisp_Array_pop(lisp_Array* array);
static void lisp_Array_shift(lisp_Array* array);
static void lisp_Array_remove(lisp_Array* array, lisp_size index);

static lisp_bool lisp_Array_equal(lisp_State* state, lisp_Array* a, lisp_Array* b);

static void lisp_Array_boot(lisp_State* state);


#endif
