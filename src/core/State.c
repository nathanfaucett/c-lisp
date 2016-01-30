#ifndef __LISP_CORE_STATE_C__
#define __LISP_CORE_STATE_C__


static lisp_State* lisp_State_new(void) {
    lisp_State* state = (lisp_State*) malloc(sizeof(lisp_State));
    state->heap = lisp_Heap_new();
    lisp_boot(state);
    return state;
}
static void lisp_State_delete(lisp_State* state) {
    lisp_Heap_delete(state->heap);
}

static void* lisp_State_alloc(lisp_State* state, size_t size) {
    return lisp_Heap_alloc(state->heap, size);
}
static void lisp_State_dealloc(lisp_State* state, void* value) {
    lisp_Heap_dealloc(state->heap, value);
}


#endif
