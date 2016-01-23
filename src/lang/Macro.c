#ifndef __LISP_LANG_MACRO_C__
#define __LISP_LANG_MACRO_C__


static void lisp_Macro_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Macro* macro = (lisp_Macro*) lisp_State_alloc(state, sizeof(lisp_Macro));
    macro->value = value;
    value->value = macro;
}
static void lisp_Macro_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Macro* fn = (lisp_Macro*) value->value;

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

static lisp_Value* lisp_Macro_call(lisp_State* state, lisp_Macro* macro, lisp_Value* args, lisp_Scope* scope) {
    if (macro->native != NULL) {
        return macro->native(state, args, scope);
    } else {
        lisp_Scope* macro_scope = lisp_Scope_new(state, scope);

        lisp_Scope_def(
            macro_scope,
            lisp_Vector_get(state, (lisp_Vector*) macro->params->value, 0),
            args
        );

        lisp_Value* value = lisp_State_eval(state, macro->body, macro_scope);
        lisp_Scope_delete(macro_scope);

        if (value->type == state->type_list) {
            return lisp_State_eval(state, value, scope);
        } else {
            return value;
        }
    }
}


#endif
