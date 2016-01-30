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


#endif
