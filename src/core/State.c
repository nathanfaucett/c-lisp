#ifndef __LISP_CORE_STATE_C__
#define __LISP_CORE_STATE_C__


static lisp_State* lisp_State_constructor(lisp_State* state) {
    state->heap = lisp_Heap_new();
    lisp_State_bootstrap(state);
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

static void lisp_State_bootstrap(lisp_State* state) {
    state->type = lisp_Type_bootstrap(state);
    state->type_any = lisp_Any_bootstrap(state);
    state->type_nil = lisp_Nil_bootstrap(state);
    state->type_char = lisp_Char_bootstrap(state);
    state->type_string = lisp_String_bootstrap(state);
    state->type_symbol = lisp_Symbol_bootstrap(state);
    state->type_list = lisp_List_bootstrap(state);

    state->nil = lisp_Value_new(state, state->type_nil);
    state->empty_list = lisp_Value_new(state, state->type_list);
    /* state->empty_vector = lisp_Value_new(state, state->type_vector); */
    /* state->empty_map = lisp_Value_new(state, state->type_map); */
}


#endif
