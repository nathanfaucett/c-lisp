#ifndef __LISP_CORE_BOOTSTRAP_C__
#define __LISP_CORE_BOOTSTRAP_C__


static void lisp_bootstrap(lisp_State* state) {
    state->type = lisp_bootstrap_Type(state);

    state->type_any = lisp_bootstrap_SubType(state, NULL, lisp_Type_empty_alloc, lisp_Type_empty_dealloc);
    state->type_nil = lisp_bootstrap_SubType(state, state->type_any, lisp_Type_empty_alloc, lisp_Type_empty_dealloc);

    state->type_bool = lisp_bootstrap_SubType(state, state->type_any, lisp_Bool_alloc, lisp_Bool_dealloc);
    state->type_char = lisp_bootstrap_SubType(state, state->type_any, lisp_Char_alloc, lisp_Char_dealloc);
    state->type_string = lisp_bootstrap_SubType(state, state->type_any, lisp_String_alloc, lisp_String_dealloc);
    state->type_symbol = lisp_bootstrap_SubType(state, state->type_any, lisp_Symbol_alloc, lisp_Symbol_dealloc);

    state->type_macro = lisp_bootstrap_SubType(state, state->type_any, lisp_Macro_alloc, lisp_Macro_dealloc);
    state->type_function = lisp_bootstrap_SubType(state, state->type_any, lisp_Function_alloc, lisp_Function_dealloc);

    state->type_list = lisp_bootstrap_SubType(state, state->type_any, lisp_List_alloc, lisp_List_dealloc);
    state->type_vector = lisp_bootstrap_SubType(state, state->type_any, lisp_Vector_alloc, lisp_Vector_dealloc);
    state->type_map = lisp_bootstrap_SubType(state, state->type_any, lisp_Map_alloc, lisp_Map_dealloc);

    state->nil = lisp_Value_new(state, state->type_nil);
    state->empty_list = lisp_Value_new(state, state->type_list);
    state->empty_vector = lisp_Value_new(state, state->type_vector);
    state->empty_map = lisp_Value_new(state, state->type_map);

    lisp_List_bootstrap(state);
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
static lisp_Value* lisp_bootstrap_SubType(
    lisp_State* state,
    lisp_Value* parent,
    void (*alloc)(lisp_State*, lisp_Value*),
    void (*dealloc)(lisp_State*, lisp_Value*)
) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor((lisp_Type*) value->value, NULL, NULL, NULL, NULL, state->type_any, alloc, dealloc);
    return value;
}

static void lisp_bootstrap_defmethod(
    lisp_State* state,
    lisp_MutList* mut_list,
    lisp_char* cstring,
    lisp_Value* (*native)(lisp_State*, lisp_Value*, lisp_Scope*)
) {
    lisp_Value* name = lisp_Value_new(state, state->type_symbol);
    lisp_Symbol_from_ascii(state, (lisp_Symbol*) name->value, "List", 0);
    lisp_MutList_push(mut_list, name);

    lisp_Value* function_value = lisp_Value_new(state, state->type_function);
    lisp_Function* function = (lisp_Function*) function_value->value;

    function->name = name;
    function->native = native;

    lisp_MutList_push(mut_list, function_value);
}

#endif
