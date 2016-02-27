#ifndef __LISP_LANG_VECTOR_H__
#define __LISP_LANG_VECTOR_H__


#define LISP_VECTOR_SHIFT 5
#define LISP_VECTOR_SIZE (1 << LISP_VECTOR_SHIFT)
#define LISP_VECTOR_MASK (LISP_VECTOR_SIZE - 1)

#define LISP_IDX_VECTOR_ROOT 0
#define LISP_IDX_VECTOR_TAIL 1
#define LISP_IDX_VECTOR_SIZE 2
#define LISP_IDX_VECTOR_SHIFT 3


static lisp_Object* lisp_Vector_init(lisp_State* state, lisp_Object* map);
static lisp_Object* lisp_Vector_new_type(lisp_State* state, lisp_Object* type);

uintsize lisp_Vector_size(lisp_Object* vector);

static lisp_Object* lisp_Vector_clone(lisp_State* state, lisp_Object* vector);

lisp_Object* lisp_Vector_from_ascii(lisp_State* state, char* ascii);
static void lisp_Vector_mut_set_size(lisp_State* state, lisp_Object* vector, uintsize size);

lisp_Object* lisp_Vector_concat(lisp_State* state, lisp_Object* a, lisp_Object* b);
uintsize lisp_Vector_index_of(lisp_State* state, lisp_Object* vector, lisp_Object* value);

static uintsize lisp_Vector_tail_off(uintsize size);
static lisp_Object* lisp_Vector_find_node(lisp_State* state, lisp_Object* vector, uintsize size);
lisp_Object* lisp_Vector_get(lisp_State* state, lisp_Object* vector, uintsize index);

static lisp_Object* lisp_Vector_new_path_set(
    lisp_State* state, lisp_Object* node, uintsize size, uintsize index, lisp_Object* value, uintsize level
);
lisp_Object* lisp_Vector_set(lisp_State* state, lisp_Object* vector, uintsize index, lisp_Object* value);
static void lisp_Vector_mut_set(lisp_State* state, lisp_Object* vector, uintsize index, lisp_Object* value);

static lisp_Object* lisp_Vector_new_path(lisp_State* state, lisp_Object* node, uintsize level);
static lisp_Object* lisp_Vector_push_tail(
    lisp_State* state, lisp_Object* parent, lisp_Object* tail_object, uintsize size, uintsize level
);
static void lisp_Vector_mut_push(lisp_State* state, lisp_Object* vector, lisp_Object* value);
lisp_Object* lisp_Vector_push(lisp_State* state, lisp_Object* vector, lisp_Object* value);

static lisp_Object* lisp_Vector_pop_tail(lisp_State* state, lisp_Object* node, uintsize size, uintsize level);
lisp_Object* lisp_Vector_pop(lisp_State* state, lisp_Object* vector);

lisp_Object* lisp_Vector_unshift(lisp_State* state, lisp_Object* vector, lisp_Object* value);

lisp_Object* lisp_Vector_remove(lisp_State* state, lisp_Object* vector, uintsize index);
static void lisp_Vector_mut_remove(lisp_State* state, lisp_Object* vector, uintsize index);

char* lisp_Vector_to_ascii(lisp_State* state, lisp_Object* vector);


#endif
