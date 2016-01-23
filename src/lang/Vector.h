#ifndef __LISP_LANG_VECTOR_H__
#define __LISP_LANG_VECTOR_H__


#define LISP_VECTOR_SHIFT 5
#define LISP_VECTOR_SIZE (1 << LISP_VECTOR_SHIFT)
#define LISP_VECTOR_MASK (LISP_VECTOR_SIZE - 1)


typedef struct lisp_VectorArray {
    lisp_u64 ref_count;
    struct lisp_Value** values;
} lisp_VectorArray;

static lisp_VectorArray* lisp_VectorArray_constructor(lisp_VectorArray*, struct lisp_Value**);
static void lisp_VectorArray_destructor(lisp_State*, lisp_VectorArray*);

static lisp_VectorArray* lisp_VectorArray_new(void);
static void lisp_VectorArray_delete(lisp_State*, lisp_VectorArray*);

static void lisp_VectorArray_copy(lisp_VectorArray*, lisp_VectorArray*, lisp_u64);

static void lisp_VectorArray_ref(lisp_VectorArray*);
static void lisp_VectorArray_deref(lisp_State*, lisp_VectorArray*);


typedef struct lisp_VectorNode {
    lisp_u64 ref_count;
    lisp_bool is_values;
    lisp_VectorArray* values;
    struct lisp_VectorNode** nodes;
} lisp_VectorNode;

static struct lisp_Value** lisp_Vector_alloc_values(void);
static lisp_VectorNode** lisp_Vector_alloc_nodes(void);

static lisp_VectorNode* lisp_VectorNode_constructor(lisp_VectorNode*, lisp_VectorArray*, lisp_VectorNode**);
static void lisp_VectorNode_destructor(lisp_State*, lisp_VectorNode*);

static lisp_VectorNode* lisp_VectorNode_new_values(void);
static lisp_VectorNode* lisp_VectorNode_new_nodes(void);
static lisp_VectorNode* lisp_VectorNode_new_tail(lisp_VectorArray*);
static void lisp_VectorNode_delete(lisp_State*, lisp_VectorNode*);

static lisp_VectorNode* lisp_VectorNode_copy(lisp_VectorNode*, lisp_VectorNode*, lisp_u64);
static lisp_VectorNode* lisp_VectorNode_clone(lisp_VectorNode*, lisp_u64);

static void lisp_VectorNode_ref(lisp_VectorNode*);
static void lisp_VectorNode_deref(lisp_State*, lisp_VectorNode*);


typedef struct lisp_Vector {
    struct lisp_Value* value;
    lisp_VectorNode* root;
    lisp_VectorArray* tail;
    lisp_u64 size;
    lisp_u64 shift;
} lisp_Vector;

static void lisp_Vector_alloc(lisp_State* state, struct lisp_Value* value);
static void lisp_Vector_dealloc(lisp_State* state, struct lisp_Value* value);

static lisp_Vector* lisp_Vector_constructor(lisp_Vector*, lisp_VectorNode*, lisp_VectorArray*, lisp_u64, lisp_u64);

static struct lisp_Value* lisp_Vector_from_mut_list(lisp_State*, lisp_MutList*);
static struct lisp_Value* lisp_Vector_from_list(lisp_State*, lisp_List*);
static struct lisp_Value* lisp_Vector_internal_new(lisp_State*);
static struct lisp_Value* lisp_Vector_clone(lisp_State*, lisp_Vector*);

static lisp_u64 lisp_Vector_size(lisp_Vector*);

static lisp_u64 lisp_Vector_tail_off(lisp_u64);
static lisp_VectorNode* lisp_Vector_get_node(lisp_Vector*, lisp_u64);
static struct lisp_VectorArray* lisp_Vector_get_nodes_for(lisp_Vector*, lisp_u64);
static struct lisp_Value* lisp_Vector_get(lisp_State*, lisp_Vector*, lisp_u64);

static lisp_VectorNode* lisp_Vector_new_path_set(lisp_State*, lisp_VectorNode*, lisp_u64, lisp_u64, struct lisp_Value*, lisp_u64);
static struct lisp_Value* lisp_Vector_set(lisp_State*, lisp_Vector*, lisp_u64, struct lisp_Value*);

static struct lisp_VectorNode* lisp_Vector_new_path(lisp_State*, lisp_VectorNode*, lisp_u64);
static struct lisp_VectorNode* lisp_Vector_push_tail(lisp_State*, lisp_VectorNode*, lisp_VectorNode*, lisp_u64, lisp_u64);

static void lisp_Vector_push_value(lisp_State*, lisp_Vector*, struct lisp_Value*);
static void lisp_Vector_push_mut_list(lisp_State*, lisp_Vector*, lisp_MutList*);

static struct lisp_Value* lisp_Vector_push(lisp_State*, lisp_Vector*, struct lisp_Value*);

static struct lisp_Value* lisp_Vector_to_string(lisp_State*, lisp_Vector*);

static lisp_bool lisp_Vector_equal(lisp_Vector*, lisp_Vector*);


#endif
