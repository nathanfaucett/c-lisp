#ifndef __LISP_LANG_FUNCTION_C__
#define __LISP_LANG_FUNCTION_C__


static void lisp_Function_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Function* function = (lisp_Function*) lisp_State_alloc(state, sizeof(lisp_Function));
    value->value = function;
    function->value = value;
    function->name = NULL;
    function->dispatches = NULL;
    function->native = NULL;
}
static void lisp_Function_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Function* fn = (lisp_Function*) value->value;

    if (fn->name != NULL) {
        lisp_Value_deref(state, fn->name);
    }
    if (fn->dispatches != NULL) {
        lisp_Value_deref(state, fn->dispatches);
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

        return function->native(state, new_list, scope);
    } else {
        return NULL;
    }
}


#endif
