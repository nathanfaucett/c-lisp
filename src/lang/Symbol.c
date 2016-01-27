#ifndef __LISP_LANG_SYMBOL_C__
#define __LISP_LANG_SYMBOL_C__


static void lisp_Symbol_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Symbol* symbol = (lisp_Symbol*) lisp_State_alloc(state, sizeof(lisp_Symbol));
    value->value = symbol;
    symbol->value = NULL;
}
static void lisp_Symbol_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Symbol* symbol = (lisp_Symbol*) value->value;
    lisp_Value_deref(state, symbol->value);
    lisp_State_dealloc(state, symbol);
}

static void lisp_Symbol_from_ascii(lisp_State* state, lisp_Symbol* symbol, lisp_char* cstring, lisp_u64 start) {
    lisp_Value* value = lisp_Value_alloc(state, state->type_string);
    symbol->value = value;
    lisp_String_from_ascii(state, (lisp_String*) value->value, cstring, start);
}
static lisp_u64 lisp_Symbol_from_utf8(lisp_State* state, lisp_Symbol* symbol, lisp_u32* cstring, lisp_u64 start) {
    lisp_Value* value = lisp_Value_alloc(state, state->type_string);
    symbol->value = value;
    return lisp_String_from_utf8(state, (lisp_String*) value->value, cstring, start);
}

static lisp_Value* lisp_Symbol_new_ascii(lisp_State* state, lisp_char* cstring) {
    lisp_Value* value = lisp_Value_alloc(state, state->type_symbol);
    lisp_Symbol_from_ascii(state, (lisp_Symbol*) value->value, cstring, 0);
    return value;
}
static lisp_Value* lisp_Symbol_new_utf8(lisp_State* state, lisp_u32* cstring) {
    lisp_Value* value = lisp_Value_alloc(state, state->type_symbol);
    lisp_Symbol_from_utf8(state, (lisp_Symbol*) value->value, cstring, 0);
    return value;
}

static lisp_bool lisp_Symbol_equal(lisp_Symbol* a, lisp_Symbol* b) {
    return lisp_String_equal((lisp_String*) a->value->value, (lisp_String*) b->value->value);
}


#endif
