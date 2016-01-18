#ifndef __LISP_CORE_SPECIAL_FORMS_C__
#define __LISP_CORE_SPECIAL_FORMS_C__


static lisp_Value* lisp_special_form_quote(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    return lisp_List_get(state, &input->list, 1);
}

static lisp_Value* lisp_special_form_def(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    lisp_Value* value = lisp_State_eval(state, lisp_List_get(state, &input->list, 2), scope);
    lisp_Scope_def(scope, lisp_List_get(state, &input->list, 1), value);
    return value;
}

static lisp_Value* lisp_special_form_swap(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    lisp_Value* value = lisp_State_eval(state, lisp_List_get(state, &input->list, 2), scope);
    lisp_Scope_swap(scope, lisp_List_get(state, &input->list, 1), value);
    return value;
}

static lisp_Value* lisp_special_form_if(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    lisp_Value* value = lisp_State_eval(state, lisp_List_get(state, &input->list, 1), scope);

    if ( /* false if return is Boolean and false */
        value->type == LISP_TYPE_BOOLEAN &&
        value->boolean.boolean_value == LISP_FALSE
    ) {
        return lisp_State_eval(state, lisp_List_get(state, &input->list, 3), scope);
    } else {
        return lisp_State_eval(state, lisp_List_get(state, &input->list, 2), scope);
    }
}

static lisp_Value* lisp_special_form_fn(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    return lisp_Value_function(
        state,
        lisp_List_get(state, &input->list, 1),
        lisp_List_get(state, &input->list, 2),
        lisp_List_get(state, &input->list, 3)
    );
}

static lisp_Value* lisp_special_form_macro(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    return lisp_Value_macro(
        state,
        lisp_List_get(state, &input->list, 1),
        lisp_List_get(state, &input->list, 2),
        lisp_List_get(state, &input->list, 3)
    );
}

static lisp_Value* lisp_special_form_do(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    lisp_Value* value = state->nil;

    for (lisp_u32 i = 1, il = lisp_List_size(&input->list); i < il; i++) {
        value = lisp_State_eval(state, lisp_List_get(state, &input->list, i), scope);

        if (i != il - 1) {
            lisp_Value_deref(state, value);
        }
    }

    return value;
}

static lisp_Value* lisp_special_form_let(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    lisp_Scope* let_scope = lisp_Scope_new(state, scope);
    lisp_Value* params = lisp_List_get(state, &input->list, 1);

    for (lisp_u32 i = 0, il = lisp_Vector_size(&params->vector); i < il; i += 2) {
        lisp_Value* param = lisp_Vector_get(state, &params->vector, i);
        lisp_Scope_def(let_scope, param,
            lisp_State_eval(state, lisp_Vector_get(state, &params->vector, i + 1), scope)
        );
    }

    lisp_Value* value = lisp_State_eval(state, lisp_List_get(state, &input->list, 2), let_scope);
    lisp_Scope_delete(let_scope);

    return value;
}

static lisp_Value* lisp_special_form_eval(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    lisp_Value* new_list = lisp_List_shift(state, &input->list);
    lisp_Value* value = lisp_State_eval(state, new_list, scope);
    lisp_Value_deref(state, new_list);
    return value;
}


#endif
