#ifndef __LISP_STATE_C__
#define __LISP_STATE_C__


static inline lisp_State* lisp_State_new(lisp_State* state) {
    lisp_Memory_new(&state->memory);
    state->nil = lisp_Value_nil(state);
    return state;
}

static inline void lisp_State_delete(lisp_State* state) {
    lisp_Memory_delete(&state->memory);
}

static inline lisp_Value* lisp_State_alloc(lisp_State* state) {
    return lisp_Memory_alloc(&state->memory);
}

static inline void lisp_State_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Memory_dealloc(&state->memory, value);
}


#endif
