#ifndef __LISP_CORE_STATE_C__
#define __LISP_CORE_STATE_C__


static lisp_State* lisp_State_constructor(lisp_State* state) {
    state->heap = lisp_Heap_new();
    lisp_bootstrap(state);
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

static lisp_Value* lisp_State_eval_list(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    lisp_ListNode* node = ((lisp_List*) input->value)->root;

    if (node != NULL) {
        lisp_Value* first = lisp_State_eval(state, node->value, scope);

        if (first->type == state->type_macro) {
            return lisp_Macro_call(state, (lisp_Macro*) first->value, lisp_List_shift(state, (lisp_List*) input->value), scope);
        } else {
            lisp_MutList* mut_list = lisp_MutList_new();
            node = node->next;

            while (node != NULL) {
                lisp_MutList_push(mut_list, lisp_State_eval(state, node->value, scope));
                node = node->next;
            }

            lisp_Value* list = lisp_List_from_mut_list(state, mut_list);
            lisp_MutList_delete(mut_list);

            if (first->type == state->type_function) {
                return lisp_Function_call(state, (lisp_Function*) first->value, list, scope);
            } else {
                return list;
            }
        }
    } else {
        return lisp_Value_ref(state->nil);
    }
}

static lisp_Value* lisp_State_eval(lisp_State* state, lisp_Value* input, lisp_Scope* scope) {
    if (input->type == state->type_list) {
        return lisp_State_eval_list(state, input, scope);
    } else if (input->type == state->type_symbol) {
        return lisp_Scope_get(scope, input);
    } else {
        return input;
    }
}


#endif
