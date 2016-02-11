#ifndef __LISP_LANG_VECTOR_H__
#define __LISP_LANG_VECTOR_H__


typedef struct lisp_Vector {
    lisp_Object* self;
    lisp_Object* root;
    lisp_Object* tail;
    lisp_usize size;
    lisp_usize shift;
} lisp_Vector;


static void lisp_Vector_alloc(lisp_State* state, lisp_Object* object);
static void lisp_Vector_mark(lisp_Object* object);

static lisp_Object* lisp_Vector_new(lisp_State* state);
static lisp_Object* lisp_Vector_clone(lisp_State* state, lisp_Vector* vector);

static void lisp_Vector_mut_set_size(lisp_State* state, lisp_Vector* vector, lisp_usize size);

static lisp_usize lisp_Vector_index_of(lisp_State* state, lisp_Vector* vector, lisp_Object* value);

static lisp_usize lisp_Vector_tail_off(lisp_usize size);
static lisp_Object* lisp_Vector_find_node(lisp_Vector* vector, lisp_usize size);
static lisp_Object* lisp_Vector_get(lisp_State* state, lisp_Vector* vector, lisp_usize index);

static lisp_Object* lisp_Vector_new_path_set(
    lisp_State* state, lisp_Object* node_object, lisp_usize size, lisp_usize index, lisp_Object* value, lisp_usize level
);
static lisp_Object* lisp_Vector_set(lisp_State* state, lisp_Vector* vector, lisp_usize index, lisp_Object* value);
static void lisp_Vector_mut_set(lisp_Vector* vector, lisp_usize index, lisp_Object* value);

static lisp_Object* lisp_Vector_new_path(lisp_State* state, lisp_Object* node_object, lisp_usize level);
static lisp_Object* lisp_Vector_push_tail(
    lisp_State* state, lisp_Object* parent_object, lisp_Object* tail_object, lisp_usize size, lisp_usize level
);
static void lisp_Vector_mut_push(lisp_State* state, lisp_Vector* vector, lisp_Object* value);
static lisp_Object* lisp_Vector_push(lisp_State* state, lisp_Vector* vector, lisp_Object* value);

static lisp_Object* lisp_Vector_pop_tail(lisp_State* state, lisp_Object* node_object, lisp_usize size, lisp_usize level);
static lisp_Object* lisp_Vector_pop(lisp_State* state, lisp_Vector* vector);

static lisp_Object* lisp_Vector_unshift(lisp_State* state, lisp_Vector* vector, lisp_Object* value);

static lisp_Object* lisp_Vector_remove(lisp_State* state, lisp_Vector* vector, lisp_usize index);
static void lisp_Vector_mut_remove(lisp_State* state, lisp_Vector* vector, lisp_usize index);

static lisp_bool lisp_Vector_equal(lisp_State* state, lisp_Vector* a, lisp_Vector* b);


#endif
