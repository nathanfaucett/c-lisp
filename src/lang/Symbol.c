#ifndef __LISP_LANG_SYMBOL_C__
#define __LISP_LANG_SYMBOL_C__


static void lisp_Symbol_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Symbol* symbol = (lisp_Symbol*) value->data;
    symbol->string = NULL;
}
static void lisp_Symbol_mark(lisp_Value* value) {
    lisp_Symbol* symbol = (lisp_Symbol*) value->data;

    if (symbol->string != NULL) {
        lisp_Value_mark(symbol->string);
    }
}

static lisp_Value* lisp_Symbol_new_ascii(lisp_State* state, lisp_char* ascii) {
    lisp_Value* value = lisp_Value_alloc(state, state->Symbol);
    lisp_Symbol* symbol = (lisp_Symbol*) value->data;
    symbol->string = lisp_String_new_ascii(state, ascii);
    return value;
}

static lisp_bool lisp_Symbol_equal(lisp_Symbol* a, lisp_Symbol* b) {
    if (a == b) {
        return LISP_TRUE;
    } else {
        if (a->string != b->string) {
            return lisp_String_equal((lisp_String*) a->string->data, (lisp_String*) b->string->data);
        } else {
            return LISP_TRUE;
        }
    }
}

static lisp_Value* lisp_export_Symbol_constructor(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    lisp_List* args_list = (lisp_List*) args->data;
    lisp_Value* self = lisp_List_get(state, args_list, 0);
    lisp_Value* value = lisp_List_get(state, args_list, 1);

    if (self->type == state->Symbol) {
        ((lisp_Symbol*) self->data)->string = lisp_Value_to_string(state, value);
    }

    return self;
}
static lisp_Value* lisp_export_Symbol_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    lisp_Value* value = lisp_Value_alloc(state, state->Bool);
    lisp_List* args_list = (lisp_List*) args->data;
    lisp_Value* self = lisp_List_get(state, args_list, 0);
    lisp_Value* other = lisp_List_get(state, args_list, 1);

    if (self->type == state->Symbol && self->type == other->type) {
        LISP_SET_DATA(value, lisp_bool, lisp_Symbol_equal((lisp_Symbol*) self->data, (lisp_Symbol*) other->data));
    } else {
        LISP_SET_DATA(value, lisp_bool, LISP_FALSE);
    }

    return value;
}
static lisp_Value* lisp_export_Symbol_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    lisp_List* args_list = (lisp_List*) args->data;
    lisp_Value* self = lisp_List_get(state, args_list, 0);

    if (self->type == state->Symbol) {
        lisp_Value* string = ((lisp_Symbol*) self->data)->string;

        if (string == NULL) {
            return state->empty_string;
        } else {
            return string;
        }
    } else {
        return state->empty_string;
    }
}

static void lisp_Symbol_boot(lisp_State* state) {
    lisp_Type* type = (lisp_Type*) state->Symbol->data;
    lisp_boot_defmethod(state, type->prototype, "constructor", lisp_export_Symbol_constructor);
    lisp_boot_defmethod(state, type->prototype, "equal", lisp_export_Symbol_equal);
    lisp_boot_defmethod(state, type->prototype, "to-string", lisp_export_Symbol_to_string);
}


#endif
