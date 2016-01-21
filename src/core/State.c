#ifndef __LISP_CORE_STATE_C__
#define __LISP_CORE_STATE_C__


static lisp_State* lisp_State_constructor(lisp_State* state) {
    state->heap = lisp_Heap_new();

    state->type_char = (lisp_Type*) malloc(sizeof(lisp_Type));
    lisp_Type_constructor(
        state->type_char,
        NULL, NULL, NULL, NULL, NULL,
        lisp_Char_alloc,
        lisp_Char_dealloc
    );

    state->type_string = (lisp_Type*) malloc(sizeof(lisp_Type));
    lisp_Type_constructor(
        state->type_string,
        NULL, NULL, NULL, NULL, NULL,
        lisp_String_alloc,
        lisp_String_dealloc
    );

    return state;
}
static void lisp_State_destructor(lisp_State* state) {
    lisp_Heap_delete(state->heap);
}

static lisp_State* lisp_State_new(void) {
    return lisp_State_constructor((lisp_State*) malloc(sizeof(lisp_State)));
}
static void lisp_State_delete(lisp_State* state) {
    lisp_State_destructor(state);
    free(state);
}

static void* lisp_State_alloc(lisp_State* state, size_t size) {
    return lisp_Heap_alloc(state->heap, size);
}
static void lisp_State_dealloc(lisp_State* state, void* value) {
    lisp_Heap_dealloc(state->heap, value);
}


#endif
