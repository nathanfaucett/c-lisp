#ifndef __LISP_CORE_STATE_C__
#define __LISP_CORE_STATE_C__


static lisp_State* lisp_State_constructor(lisp_State* state) {
    state->memory = lisp_Memory_new();
    state->global = lisp_Scope_new(state, NULL);

    lisp_Value* quote = lisp_Value_symbol_from_cstring(state, "quote");
    lisp_Scope_def(state->global, quote, lisp_Value_native_macro(state, quote, lisp_special_form_quote));

    lisp_Value* def = lisp_Value_symbol_from_cstring(state, "def");
    lisp_Scope_def(state->global, def, lisp_Value_native_macro(state, def, lisp_special_form_def));

    lisp_Value* swap = lisp_Value_symbol_from_cstring(state, "swap");
    lisp_Scope_def(state->global, swap, lisp_Value_native_macro(state, swap, lisp_special_form_swap));

    lisp_Value* _if = lisp_Value_symbol_from_cstring(state, "if");
    lisp_Scope_def(state->global, _if, lisp_Value_native_macro(state, _if, lisp_special_form_if));

    lisp_Value* fn = lisp_Value_symbol_from_cstring(state, "fn");
    lisp_Scope_def(state->global, fn, lisp_Value_native_macro(state, fn, lisp_special_form_fn));

    lisp_Value* macro = lisp_Value_symbol_from_cstring(state, "macro");
    lisp_Scope_def(state->global, macro, lisp_Value_native_macro(state, macro, lisp_special_form_macro));

    lisp_Value* _do = lisp_Value_symbol_from_cstring(state, "do");
    lisp_Scope_def(state->global, _do, lisp_Value_native_macro(state, _do, lisp_special_form_do));

    lisp_Value* let = lisp_Value_symbol_from_cstring(state, "let");
    lisp_Scope_def(state->global, let, lisp_Value_native_macro(state, let, lisp_special_form_let));

    state->nil = lisp_Value_new_nil(state);
    state->empty_list = lisp_Value_new_list(state);
    state->empty_vector = lisp_Value_new_vector(state);

    return state;
}

static void lisp_State_destructor(lisp_State* state) {
    lisp_Scope_delete(state->global);
    lisp_Memory_delete(state->memory);
}

static lisp_State* lisp_State_new(void) {
    return lisp_State_constructor((lisp_State*) malloc(sizeof(lisp_State)));
}

static void lisp_State_delete(lisp_State* state) {
    lisp_State_destructor(state);
    free(state);
}

static lisp_Value* lisp_State_alloc(lisp_State* state) {
    return lisp_Memory_alloc(state->memory);
}

static void lisp_State_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Memory_dealloc(state->memory, value);
}

static lisp_Value* lisp_State_eval_list(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    lisp_MutList* mut_list = lisp_MutList_new();
    lisp_ListNode* node = input->list.root;

    while (node != NULL) {
        lisp_MutList_push(mut_list, lisp_State_eval(state, node->value, scope));
        node = node->next;
    }

    lisp_Value* list = lisp_Value_list_from_mut_list(state, mut_list);
    lisp_MutList_delete(mut_list);

    lisp_Value* first = lisp_List_get(state, &list->list, 0);

    if (first->type == LISP_TYPE_FUNCTION) {
        return lisp_Function_call(state, &first->function, lisp_List_shift(state, &list->list), scope);
    } else if (first->type == LISP_TYPE_MACRO) {
        return lisp_Macro_call(state, &first->macro, input, scope);
    } else {
        return list;
    }
}

static lisp_Value* lisp_State_eval(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    if (input->type == LISP_TYPE_LIST) {
        return lisp_State_eval_list(state, input, scope);
    } else if (input->type == LISP_TYPE_SYMBOL) {
        return lisp_Scope_get(scope, input);
    } else {
        return input;
    }
}

static lisp_Value* lisp_State_parse(lisp_State* state, lisp_u8* input, lisp_Scope* scope) {
    lisp_Reader* reader = lisp_Reader_new(state, input);

    lisp_Value* read_value = lisp_Reader_next(reader, '\0');
    lisp_Value* value = NULL;

    while (LISP_TRUE) {
        value = lisp_State_eval(state, read_value, scope);
        read_value = lisp_Reader_next(reader, '\0');

        if (read_value != NULL && value != NULL) {
            lisp_Value_deref(state, value);
        } else {
            break;
        }
    }

    lisp_Reader_delete(reader);
    return value;
}


#endif
