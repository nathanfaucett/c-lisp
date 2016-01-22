#ifndef __LISP_CORE_STATE_H__
#define __LISP_CORE_STATE_H__


typedef struct lisp_State {
    struct lisp_Heap* heap;

    struct lisp_Value* type;
    struct lisp_Value* type_any;
    struct lisp_Value* type_nil;

    struct lisp_Value* type_char;
    struct lisp_Value* type_string;
    struct lisp_Value* type_symbol;

    struct lisp_Value* type_number;

    struct lisp_Value* type_list;
    struct lisp_Value* type_vector;
    struct lisp_Value* type_map;

    struct lisp_Value* nil;
    struct lisp_Value* empty_list;
    struct lisp_Value* empty_vector;
    struct lisp_Value* empty_map;
} lisp_State;


static lisp_State* lisp_State_constructor(lisp_State* state);
static void lisp_State_destructor(lisp_State* state);

static lisp_State* lisp_State_new(void);
static void lisp_State_delete(lisp_State* state);

static void* lisp_State_alloc(lisp_State* state, size_t size);
static void lisp_State_dealloc(lisp_State* state, void* value);

static void lisp_State_bootstrap(lisp_State* state);


#endif
