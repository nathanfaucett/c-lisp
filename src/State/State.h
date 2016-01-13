#ifndef __LISP_STATE_H__
#define __LISP_STATE_H__


typedef struct lisp_State {
    struct lisp_Value* nil;
    struct lisp_Value* empty_list;
    lisp_Memory memory;
} lisp_State;


static inline lisp_State* lisp_State_new(lisp_State*);
static inline void lisp_State_delete(lisp_State*);

static inline struct lisp_Value* lisp_State_alloc(lisp_State*);
static inline void lisp_State_dealloc(lisp_State*, struct lisp_Value*);


#endif
