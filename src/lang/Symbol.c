#ifndef __LISP_LANG_SYMBOL_C__
#define __LISP_LANG_SYMBOL_C__


inline static struct lisp_Symbol* lisp_Symbol_cstring(lisp_State* state, lisp_Symbol* symbol, lisp_u8* cstring) {
    symbol->string = lisp_Value_string(state, cstring);
    return symbol;
}

inline static void lisp_Symbol_delete(lisp_State* state, lisp_Symbol* symbol) {
    lisp_Value_deref(state, symbol->string);
}

inline static struct lisp_Value* lisp_Symbol_to_string(lisp_State* state, lisp_Symbol* symbol) {
    lisp_Value* value = symbol->string;
    lisp_Value_ref(value);
    return value;
}


#endif
