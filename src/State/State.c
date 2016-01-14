#ifndef __LISP_STATE_C__
#define __LISP_STATE_C__


static inline lisp_State* lisp_State_constructor(lisp_State* state) {
    state->memory = lisp_Memory_new();
    state->nil = lisp_Value_new_nil(state);
    state->empty_list = lisp_Value_new_list(state);
    return state;
}

static inline void lisp_State_destructor(lisp_State* state) {
    lisp_Memory_delete(state->memory);
}

static inline lisp_State* lisp_State_new(void) {
    return lisp_State_constructor((lisp_State*) malloc(sizeof(lisp_State)));
}

static inline void lisp_State_delete(lisp_State* state) {
    lisp_State_destructor(state);
    free(state);
}

static inline lisp_Value* lisp_State_alloc(lisp_State* state) {
    return lisp_Memory_alloc(state->memory);
}

static inline void lisp_State_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Memory_dealloc(state->memory, value);
}


#endif
