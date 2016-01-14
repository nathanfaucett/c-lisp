#ifndef __LISP_CORE_STATE_H__
#define __LISP_CORE_STATE_H__


typedef struct lisp_State {
    struct lisp_Value* nil;
    struct lisp_Value* empty_list;
    struct lisp_Value* empty_vector;
    lisp_Memory* memory;
} lisp_State;


static lisp_State* lisp_State_constructor(lisp_State*);
static void lisp_State_destructor(lisp_State*);

static lisp_State* lisp_State_new(void);
static void lisp_State_delete(lisp_State*);

static struct lisp_Value* lisp_State_alloc(lisp_State*);
static void lisp_State_dealloc(lisp_State*, struct lisp_Value*);


#endif
