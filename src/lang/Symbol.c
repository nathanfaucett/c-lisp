#ifndef __LISP_LANG_SYMBOL_C__
#define __LISP_LANG_SYMBOL_C__


static lisp_Value* lisp_Symbol_from_ascii(lisp_State* state, lisp_char* ascii) {
    lisp_Value* value = lisp_Value_alloc(state, state->Symbol);
    lisp_Array_set((lisp_Array*) value->values->data, 0, lisp_String_from_ascii(state, ascii));
    return value;
}

static void lisp_Symbol_boot(lisp_State* state) {
    lisp_Value* Symbol = state->Symbol;
    lisp_Array* attributes = (lisp_Array*) lisp_Array_get(state, (lisp_Array*) Symbol->values->data, LISP_IDX_TYPE_ATTRIBUTES)->data;
    lisp_Array_push(attributes, lisp_Symbol_from_ascii(state, "string"));
}


#endif
