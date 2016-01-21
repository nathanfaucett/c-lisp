#ifndef __LISP_CORE_STATE_H__
#define __LISP_CORE_STATE_H__


typedef struct lisp_State {
    struct lisp_Heap* heap;
    struct lisp_Type* type_list;
    struct lisp_Type* type_char;
    struct lisp_Type* type_string;
} lisp_State;


static lisp_State* lisp_State_constructor(lisp_State* state);
static void lisp_State_destructor(lisp_State* state);

static lisp_State* lisp_State_new(void);
static void lisp_State_delete(lisp_State* state);

static void* lisp_State_alloc(lisp_State* state, size_t size);
static void lisp_State_dealloc(lisp_State* state, void* value);


#endif
