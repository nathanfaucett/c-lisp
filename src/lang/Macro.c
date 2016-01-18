#ifndef __LISP_LANG_MACRO_C__
#define __LISP_LANG_MACRO_C__


static lisp_Macro* lisp_Macro_constructor(
    lisp_Macro* macro, lisp_Value* name, lisp_Value* params, lisp_Value* body
) {
    macro->name = name;
    macro->params = params;
    macro->body = body;

    macro->symbol = NULL;
    macro->native = NULL;

    return macro;
}

static void lisp_Macro_destructor(lisp_State* state, lisp_Macro* macro) {
    if (macro->symbol != NULL) {
        lisp_Value_deref(state, macro->symbol);
    } else {
        lisp_Value_deref(state, macro->name);
        lisp_Value_deref(state, macro->params);
        lisp_Value_deref(state, macro->body);
    }
}

static lisp_Value* lisp_Macro_call(lisp_State* state, lisp_Macro* macro, lisp_Value* values, lisp_Scope* scope) {
    if (macro->native != NULL) {
        return macro->native(state, values, scope);
    } else {
        lisp_Scope* macro_scope = lisp_Scope_new(state, scope);

        lisp_Scope_def(
            macro_scope,
            lisp_Vector_get(state, &macro->params->vector, 0),
            values
        );

        lisp_Value* value = lisp_State_eval(state, macro->body, macro_scope);
        lisp_Scope_delete(macro_scope);

        if (value->type == LISP_TYPE_LIST) {
            return lisp_State_eval(state, value, scope);
        } else {
            return value;
        }
    }
}

static struct lisp_Value* lisp_Macro_to_string(lisp_State* state, lisp_Macro* macro) {
    if (macro->native != NULL) {
        return lisp_Value_to_string(state, macro->symbol);
    } else {
        return lisp_Value_to_string(state, macro->name);
    }
}

static lisp_bool lisp_Macro_equal(lisp_Macro* a, lisp_Macro* b) {
    return a == b;
}


#endif
