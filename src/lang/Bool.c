#ifndef __LISP_LANG_BOOL_C__
#define __LISP_LANG_BOOL_C__


static void lisp_Bool_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Bool* bool = (lisp_Bool*) lisp_State_alloc(state, sizeof(lisp_Bool));
    value->value = bool;
    bool->value = LISP_TRUE;
}
static void lisp_Bool_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_State_dealloc(state, value->value);
}

static lisp_Value* lisp_export_Bool_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    lisp_List* args_list = (lisp_List*) args->value;
    lisp_Value* ret = lisp_Value_alloc(state, state->type_bool);

    lisp_Value* a = lisp_List_get(state, args_list, 0);
    lisp_Value* b = lisp_List_get(state, args_list, 1);

    if (a->type == state->type_bool && a->type == b->type) {
        ((lisp_Bool*) ret->value)->value = ((lisp_Bool*) a->value)->value == ((lisp_Bool*) b->value)->value;
    } else {
        ((lisp_Bool*) ret->value)->value = LISP_FALSE;
    }

    return ret;
}

static lisp_Value* lisp_export_Bool_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    lisp_List* args_list = (lisp_List*) args->value;
    lisp_Value* self = lisp_List_get(state, args_list, 0);

    if (self->type != state->type_bool || ((lisp_Bool*) self->value)->value) {
        return lisp_String_new_ascii(state, "true");
    } else {
        return lisp_String_new_ascii(state, "false");
    }
}

static void lisp_Bool_bootstrap(lisp_State* state) {
    lisp_Type* type = (lisp_Type*) state->type_bool->value;
    type->name = lisp_Symbol_new_ascii(state, "Bool");

    lisp_MutList* mut_list = lisp_MutList_new();

    lisp_bootstrap_defmethod(state, mut_list, "equal", lisp_export_Bool_equal);
    lisp_bootstrap_defmethod(state, mut_list, "to-string", lisp_export_Bool_to_string);

    type->prototype = lisp_Map_from_mut_list(state, mut_list);
    lisp_MutList_delete(mut_list);
}


#endif
