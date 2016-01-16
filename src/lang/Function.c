#ifndef __LISP_LANG_FUNCTION_C__
#define __LISP_LANG_FUNCTION_C__


static lisp_Function* lisp_Function_constructor(
    lisp_Function* fn, lisp_Value* name, lisp_Value* params, lisp_Value* body
) {
    fn->name = name;
    fn->params = params;
    fn->body = body;
    return fn;
}

static void lisp_Function_destructor(lisp_State* state, lisp_Function* fn) {
    lisp_Value_deref(state, fn->name);
    lisp_Value_deref(state, fn->params);
    lisp_Value_deref(state, fn->body);
}

static lisp_Value* lisp_Function_call(lisp_State* state, lisp_Function* fn, lisp_Value* values, lisp_Scope* scope) {
    lisp_Scope* fn_scope = lisp_Scope_new(state, scope);
    lisp_bool rest = LISP_FALSE;

    for (lisp_u32 i = 0, il = lisp_Vector_size(&fn->params->vector); i < il; i++) {
        lisp_Value* param = lisp_Vector_get(state, &fn->params->vector, i);

        if (rest) {
            /* fixme */
        } else {
            lisp_u8* cstring = lisp_String_to_cstring(&param->symbol.string->string);

            if (lisp_cstring_equal(cstring, "...")) {
                rest = LISP_TRUE;
            } else {
                lisp_Scope_def(fn_scope, param, lisp_List_get(state, &values->list, i));
            }

            free(cstring);
        }
    }

    return lisp_State_eval(state, fn->body, fn_scope);
}

static struct lisp_Value* lisp_Function_to_string(lisp_State* state, lisp_Function* fn) {
    return lisp_Value_to_string(state, fn->name);
}

static lisp_bool lisp_Function_equal(lisp_Function* a, lisp_Function* b) {
    return a == b;
}


#endif
