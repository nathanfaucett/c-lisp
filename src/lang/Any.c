#ifndef __LISP_LANG_ANY_C__
#define __LISP_LANG_ANY_C__


static lisp_Value* lisp_export_Any_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    lisp_List* args_list = (lisp_List*) args->value;
    lisp_Value* ret = lisp_Value_alloc(state, state->type_bool);

    lisp_Value* a = lisp_List_get(state, args_list, 0);
    lisp_Value* b = lisp_List_get(state, args_list, 1);

    if (a->type != b->type) {
        ((lisp_Bool*) ret->value)->value = LISP_FALSE;
    } else {
        ((lisp_Bool*) ret->value)->value = lisp_List_equal(state, (lisp_List*) a->values->value, (lisp_List*) a->values->value, scope);
    }

    return ret;
}

static lisp_Value* lisp_export_Any_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return lisp_String_new_ascii(state, "()");
}

static void lisp_Any_bootstrap(lisp_State* state) {
    lisp_Type* type = (lisp_Type*) state->type_any->value;

    type->name = lisp_Symbol_new_ascii(state, "Any");

    lisp_MutList* mut_list = lisp_MutList_new();

    lisp_bootstrap_defmethod(state, mut_list, "equal", lisp_export_Any_equal);
    lisp_bootstrap_defmethod(state, mut_list, "to-string", lisp_export_Any_to_string);

    type->prototype = lisp_Map_from_mut_list(state, mut_list);
    lisp_MutList_delete(mut_list);
}


#endif
