#ifndef __LISP_LANG_FUNCTION_C__
#define __LISP_LANG_FUNCTION_C__


static void lisp_Function_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Function* function = (lisp_Function*) lisp_State_alloc(state, sizeof(lisp_Function));
    function->value = value;
    value->value = function;
}
static void lisp_Function_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Function* fn = (lisp_Function*) value->value;

    if (fn->name != NULL) {
        lisp_Value_deref(state, fn->name);
    }
    if (fn->params != NULL) {
        lisp_Value_deref(state, fn->params);
    }
    if (fn->body != NULL) {
        lisp_Value_deref(state, fn->body);
    }

    lisp_State_dealloc(state, value->value);
}

static lisp_Value* lisp_Function_call(lisp_State* state, lisp_Function* function, lisp_Value* args_value, lisp_Scope* scope) {
    if (function->native != NULL) {
        lisp_MutList* mut_list = lisp_MutList_new();
        lisp_ListNode* node = ((lisp_List*) args_value->value)->root;

        while (node != NULL) {
            lisp_MutList_push(mut_list, lisp_State_eval(state, (lisp_Value*) node->value, scope));
            node = node->next;
        }

        lisp_Value* new_list = lisp_List_from_mut_list(state, mut_list);
        lisp_MutList_delete(mut_list);

        lisp_Value* value = function->native(state, new_list, scope);

        return value;
    } else {
        lisp_Scope* function_scope = lisp_Scope_new(state, scope);
        lisp_List* args = (lisp_List*) args_value->value;
        lisp_Vector* params = (lisp_Vector*) function->params->value;
        lisp_bool rest = LISP_FALSE;

        if (function->name != NULL) {
            lisp_Scope_def(function_scope, function->name, function->value);
        }

        for (lisp_u64 i = 0, il = params->size; i < il; i++) {
            lisp_Value* param = lisp_Vector_get(state, params, i);

            if (rest) {
                lisp_Value* new_list = lisp_List_after(state, args, i - 1);
                lisp_Value* new_vector = lisp_Vector_from_list(state, (lisp_List*) new_list->value);
                lisp_Scope_def(function_scope, param, lisp_State_eval(state, new_vector, scope));
                break;
            } else {
                lisp_char* cstring = lisp_String_to_cstring((lisp_String*) ((lisp_Symbol*) param->value)->value);

                if (lisp_cstring_equal(cstring, "...")) {
                    rest = LISP_TRUE;
                } else {
                    lisp_Scope_def(function_scope, param, lisp_State_eval(state, lisp_List_get(state, args, i), scope));
                }

                free(cstring);
            }
        }

        lisp_Value* value = lisp_State_eval(state, function->body, function_scope);
        lisp_Scope_delete(function_scope);

        return value;
    }
}


#endif
