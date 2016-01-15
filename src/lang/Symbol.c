#ifndef __LISP_LANG_SYMBOL_C__
#define __LISP_LANG_SYMBOL_C__


static void lisp_Symbol_destructor(lisp_State* state, lisp_Symbol* symbol) {
    lisp_Value_deref(state, symbol->string);
}

static lisp_Symbol* lisp_Symbol_from_cstring(lisp_State* state, lisp_Symbol* symbol, lisp_u8* cstring) {
    symbol->string = lisp_Value_string_from_cstring(state, cstring);
    return symbol;
}

static lisp_Value* lisp_Symbol_to_string(lisp_State* state, lisp_Symbol* symbol) {
    lisp_Value* value = symbol->string;
    lisp_Value_ref(value);
    return value;
}

static lisp_bool lisp_Symbol_equal(lisp_Symbol* a, lisp_Symbol* b) {
    return lisp_String_equal(&a->string->string, &b->string->string);
}


#endif
