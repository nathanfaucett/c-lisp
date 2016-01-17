#ifndef __LISP_LANG_MACRO_C__
#define __LISP_LANG_MACRO_C__


static lisp_Macro* lisp_Macro_constructor(
    lisp_Macro* fn, lisp_Value* name, lisp_Value* params, lisp_Value* body
) {
    fn->name = name;
    fn->params = params;
    fn->body = body;

    fn->symbol = NULL;
    fn->native = NULL;

    return fn;
}

static void lisp_Macro_destructor(lisp_State* state, lisp_Macro* fn) {
    lisp_Value_deref(state, fn->name);
    lisp_Value_deref(state, fn->params);
    lisp_Value_deref(state, fn->body);

    if (fn->symbol != NULL) {
        lisp_Value_deref(state, fn->symbol);
    }
}

static lisp_Value* lisp_Macro_call(lisp_State* state, lisp_Macro* fn, lisp_Value* values, lisp_Scope* scope) {
    if (fn->native != NULL) {
        return fn->native(state, values, scope);
    } else {
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

        lisp_Value* value = lisp_State_eval(state, fn->body, fn_scope);
        lisp_Scope_delete(fn_scope);

        if (value->type == LISP_TYPE_LIST) {
            return lisp_State_eval(state, value, scope);
        } else {
            return value;
        }
    }
}

static struct lisp_Value* lisp_Macro_to_string(lisp_State* state, lisp_Macro* fn) {
    if (fn->native != NULL) {
        return lisp_Value_to_string(state, fn->symbol);
    } else {
        return lisp_Value_to_string(state, fn->name);
    }
}

static lisp_bool lisp_Macro_equal(lisp_Macro* a, lisp_Macro* b) {
    return a == b;
}


#endif
