#ifndef __LISP_LANG_SYMBOL_C__
#define __LISP_LANG_SYMBOL_C__


static void lisp_Symbol_alloc(lisp_State* state, lisp_Object* object) {
    lisp_Symbol* symbol = (lisp_Symbol*) object->data;
    symbol->value = NULL;
}
static void lisp_Symbol_mark(lisp_Object* object) {
    lisp_Symbol* symbol = (lisp_Symbol*) object->data;

    if (symbol->value != NULL) {
        lisp_Object_mark(symbol->value);
    }
}

static lisp_Object* lisp_Symbol_from_ascii(lisp_State* state, lisp_char* ascii) {
    lisp_Object* object = lisp_Object_alloc(state, state->Symbol);
    lisp_Symbol* symbol = (lisp_Symbol*) object->data;
    symbol->value = lisp_String_from_ascii(state, ascii);
    return object;
}
static lisp_bool lisp_Symbol_equal(lisp_Symbol* a, lisp_Symbol* b) {
    if (a == b || a->value == b->value) {
        return LISP_TRUE;
    } else if (a->value != NULL && b->value != NULL) {
        return lisp_String_equal((lisp_String*) a->value->data, (lisp_String*) b->value->data);
    } else {
        return LISP_FALSE;
    }
}

static lisp_Object* lisp_Symbol_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Object* self = lisp_List_get(state, (lisp_List*) args->data, 0);

    if (self->type == state->Symbol) {
        lisp_Symbol* symbol = (lisp_Symbol*) self->data;

        if (symbol->value != NULL) {
            return symbol->value;
        } else {
            return state->empty_string;
        }
    } else {
        return lisp_Object_to_string(state, self);
    }
}
static lisp_Object* lisp_Symbol_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_List* list = (lisp_List*) args->data;
    lisp_Object* self = lisp_List_get(state, list, 0);
    lisp_Object* other = lisp_List_get(state, list, 1);

    if (self->type == state->Symbol && other->type == state->Symbol) {
        return lisp_Symbol_equal((lisp_Symbol*) self->data, (lisp_Symbol*) other->data) ? state->true : state->false;
    } else {
        return lisp_Object_equal(state, self, other) ? state->true : state->false;
    }
}

static void lisp_Symbol_boot(lisp_State* state) {
    lisp_Object* Symbol = state->Symbol;
    lisp_List* values = (lisp_List*) Symbol->values->data;
    lisp_Map* prototype = (lisp_Map*) lisp_List_get(state, values, LISP_IDX_TYPE_PROTOTYPE)->data;

    lisp_List_mut_set(values, LISP_IDX_TYPE_NAME, lisp_String_from_ascii(state, "Symbol"));

    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "to-string"), lisp_Native_new(state, lisp_Symbol_export_to_string));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "equal"), lisp_Native_new(state, lisp_Symbol_export_equal));
}


#endif
