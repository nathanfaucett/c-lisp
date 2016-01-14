#ifndef __LISP_LANG_SYMBOL_C__
#define __LISP_LANG_SYMBOL_C__


static void lisp_Symbol_destructor(lisp_State* state, lisp_Symbol* symbol) {
    lisp_Value_deref(state, symbol->string);
}

static struct lisp_Symbol* lisp_Symbol_from_cstring(lisp_State* state, lisp_Symbol* symbol, lisp_u8* cstring) {
    symbol->string = lisp_Value_string_from_cstring(state, cstring);
    return symbol;
}

static lisp_Value* lisp_Symbol_to_string(lisp_State* state, lisp_Symbol* symbol) {
    lisp_Value* value = symbol->string;
    lisp_Value_ref(value);
    return value;
}


#endif
