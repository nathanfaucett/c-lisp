#ifndef __LISP_CORE_BOOTSTRAP_C__
#define __LISP_CORE_BOOTSTRAP_C__


static void lisp_bootstrap(lisp_State* state) {
    state->type = lisp_bootstrap_Type(state);

    state->type_any = lisp_bootstrap_Any(state);
    state->type_nil = lisp_bootstrap_Nil(state);

    state->type_bool = lisp_bootstrap_Bool(state);
    state->type_char = lisp_bootstrap_Char(state);
    state->type_string = lisp_bootstrap_String(state);
    state->type_symbol = lisp_bootstrap_Symbol(state);

    state->type_function = lisp_bootstrap_Function(state);

    state->type_list = lisp_bootstrap_List(state);
    state->type_vector = lisp_bootstrap_Vector(state);
    state->type_map = lisp_bootstrap_Map(state);

    state->nil = lisp_Value_new(state, state->type_nil);
    state->empty_list = lisp_Value_new(state, state->type_list);
    state->empty_vector = lisp_Value_new(state, state->type_vector);
    state->empty_map = lisp_Value_new(state, state->type_map);
}

static lisp_Value* lisp_bootstrap_Type(lisp_State* state) {
    lisp_Type* type = (lisp_Type*) malloc(sizeof(lisp_Type));
    lisp_Type_constructor(
        type,
        NULL, NULL, NULL, NULL, NULL,
        lisp_Type_alloc,
        lisp_Type_dealloc
    );

    lisp_Value* value = lisp_State_alloc(state, sizeof(lisp_Value));
    value->ref_count = 1;
    value->type = NULL;
    value->value = type;
    value->values = NULL;

    return value;
}
static lisp_Value* lisp_bootstrap_Any(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL, NULL,
        lisp_Type_empty_alloc,
        lisp_Type_empty_dealloc
    );
    return value;
}
static lisp_Value* lisp_bootstrap_Nil(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_Type_empty_alloc,
        lisp_Type_empty_dealloc
    );
    return value;
}
static lisp_Value* lisp_bootstrap_Function(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_Function_alloc,
        lisp_Function_dealloc
    );
    return value;
}
static lisp_Value* lisp_bootstrap_Bool(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_Bool_alloc,
        lisp_Bool_dealloc
    );
    return value;
}
static lisp_Value* lisp_bootstrap_Char(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_Char_alloc,
        lisp_Char_dealloc
    );
    return value;
}
static lisp_Value* lisp_bootstrap_String(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_String_alloc,
        lisp_String_dealloc
    );
    return value;
}
static lisp_Value* lisp_bootstrap_Symbol(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_Symbol_alloc,
        lisp_Symbol_dealloc
    );
    return value;
}
static lisp_Value* lisp_bootstrap_List(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_List_alloc,
        lisp_List_dealloc
    );
    return value;
}
static lisp_Value* lisp_bootstrap_Vector(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_Vector_alloc,
        lisp_Vector_dealloc
    );
    return value;
}
static lisp_Value* lisp_bootstrap_Map(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_Map_alloc,
        lisp_Map_dealloc
    );
    return value;
}


#endif
