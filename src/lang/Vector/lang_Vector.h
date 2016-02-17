#ifndef __LISP_LANG_VECTOR_H__
#define __LISP_LANG_VECTOR_H__


#define LISP_VECTOR_SHIFT 5
#define LISP_VECTOR_SIZE (1 << LISP_VECTOR_SHIFT)
#define LISP_VECTOR_MASK (LISP_VECTOR_SIZE - 1)


typedef struct lisp_Vector {
    lisp_Object* self;
    lisp_VectorNode* root;
    lisp_VectorNode* tail;
    uintsize size;
    uintsize shift;
} lisp_Vector;


static void lisp_Vector_alloc(lisp_State* state, lisp_Object* object);
static void lisp_Vector_mark(lisp_Object* object);

static lisp_Object* lisp_Vector_new(lisp_State* state, lisp_Object* template);
static lisp_Object* lisp_Vector_new_type(lisp_State* state, lisp_Object* Type);
static lisp_Object* lisp_Vector_clone(lisp_State* state, lisp_Vector* vector);

static lisp_Object* lisp_Vector_from_ascii(lisp_State* state, char* ascii);
static void lisp_Vector_mut_set_size(lisp_State* state, lisp_Vector* vector, uintsize size);

static lisp_Object* lisp_Vector_concat(lisp_State* state, lisp_Vector* a, lisp_Vector* b);
static uintsize lisp_Vector_index_of(lisp_State* state, lisp_Vector* vector, lisp_Object* value);

static uintsize lisp_Vector_tail_off(uintsize size);
static lisp_VectorNode* lisp_Vector_find_node(lisp_Vector* vector, uintsize size);
static lisp_Object* lisp_Vector_get(lisp_State* state, lisp_Vector* vector, uintsize index);

static lisp_VectorNode* lisp_Vector_new_path_set(
    lisp_State* state, lisp_VectorNode* node, uintsize size, uintsize index, lisp_Object* value, uintsize level
);
static lisp_Object* lisp_Vector_set(lisp_State* state, lisp_Vector* vector, uintsize index, lisp_Object* value);
static void lisp_Vector_mut_set(lisp_Vector* vector, uintsize index, lisp_Object* value);

static lisp_VectorNode* lisp_Vector_new_path(lisp_State* state, lisp_VectorNode* node, uintsize level);
static lisp_VectorNode* lisp_Vector_push_tail(
    lisp_State* state, lisp_VectorNode* parent, lisp_VectorNode* tail, uintsize size, uintsize level
);
static void lisp_Vector_mut_push(lisp_State* state, lisp_Vector* vector, lisp_Object* value);
static lisp_Object* lisp_Vector_push(lisp_State* state, lisp_Vector* vector, lisp_Object* value);

static lisp_VectorNode* lisp_Vector_pop_tail(lisp_State* state, lisp_VectorNode* node, uintsize size, uintsize level);
static lisp_Object* lisp_Vector_pop(lisp_State* state, lisp_Vector* vector);

static lisp_Object* lisp_Vector_unshift(lisp_State* state, lisp_Vector* vector, lisp_Object* value);

static lisp_Object* lisp_Vector_remove(lisp_State* state, lisp_Vector* vector, uintsize index);
static void lisp_Vector_mut_remove(lisp_State* state, lisp_Vector* vector, uintsize index);

static bool lisp_Vector_equal(lisp_State* state, lisp_Vector* a, lisp_Vector* b);


#endif
