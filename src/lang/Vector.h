#ifndef __LISP_LANG_VECTOR_H__
#define __LISP_LANG_VECTOR_H__


#define LISP_VECTOR_SHIFT 5
#define LISP_VECTOR_SIZE (1 << LISP_VECTOR_SHIFT)
#define LISP_VECTOR_MASK (LISP_VECTOR_SIZE - 1)


typedef struct lisp_VectorNode {
    lisp_u32 ref_count;
    lisp_u32 size;
    lisp_bool is_values;
    struct lisp_Value** values;
    struct lisp_VectorNode** array;
} lisp_VectorNode;

static lisp_VectorNode* lisp_VectorNode_values_constructor(lisp_VectorNode*, struct lisp_Value**);
static lisp_VectorNode* lisp_VectorNode_array_constructor(lisp_VectorNode*, lisp_VectorNode**);

static lisp_VectorNode* lisp_VectorNode_new_values(void);
static lisp_VectorNode* lisp_VectorNode_new_array(void);
static lisp_VectorNode* lisp_VectorNode_new_tail(lisp_Value*);
static void lisp_VectorNode_delete(lisp_State*, lisp_VectorNode*);

static lisp_VectorNode* lisp_VectorNode_copy(lisp_VectorNode*, lisp_VectorNode*, lisp_u32);
static lisp_VectorNode* lisp_VectorNode_clone(lisp_VectorNode*, lisp_u32);

static void lisp_VectorNode_ref(lisp_VectorNode*);
static void lisp_VectorNode_deref(lisp_State*, lisp_VectorNode*);


typedef struct lisp_Vector {
    struct lisp_Value* value;
    lisp_VectorNode* root;
    struct lisp_Value** tail;
    lisp_u32 size;
    lisp_u32 shift;
} lisp_Vector;


static lisp_Vector* lisp_Vector_constructor(lisp_Vector*, lisp_VectorNode*, struct lisp_Value**, lisp_u32, lisp_u32);
static void lisp_Vector_destructor(lisp_State*, lisp_Vector*);

static struct lisp_Value* lisp_Vector_from_array(lisp_State*, lisp_Array*);
static struct lisp_Value* lisp_Vector_internal_new(lisp_State*);
static struct lisp_Value* lisp_Vector_clone(lisp_State*, lisp_Vector*);

static lisp_u32 lisp_Vector_tail_off(lisp_u32);
static lisp_VectorNode* lisp_Vector_get_node(lisp_Vector*, lisp_u32);
static struct lisp_Value** lisp_Vector_get_array_for(lisp_Vector*, lisp_u32);
static struct lisp_Value* lisp_Vector_get(lisp_State*, lisp_Vector*, lisp_u32);

static lisp_VectorNode* lisp_Vector_new_path_set(lisp_VectorNode*, lisp_u32, lisp_u32, struct lisp_Value*, lisp_u32);
static struct lisp_Value* lisp_Vector_set(lisp_State*, lisp_Vector*, lisp_u32, struct lisp_Value*);

static struct lisp_VectorNode* lisp_Vector_new_path(lisp_VectorNode*, lisp_u32);
static struct lisp_VectorNode* lisp_Vector_push_tail(lisp_VectorNode*, lisp_VectorNode*, lisp_u32, lisp_u32);

static void lisp_Vector_push_value(lisp_Vector*, lisp_Value*);
static void lisp_Vector_push_array(lisp_Vector*, lisp_Array*);

static struct lisp_Value* lisp_Vector_to_string(lisp_State*, lisp_Vector*);

static lisp_bool lisp_Vector_equal(lisp_Vector*, lisp_Vector*);


#endif
