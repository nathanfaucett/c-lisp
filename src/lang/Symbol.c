#ifndef __LISP_LANG_SYMBOL_C__
#define __LISP_LANG_SYMBOL_C__


static lisp_Value* lisp_Symbol_from_ascii(lisp_State* state, lisp_char* ascii) {
    lisp_Value* value = lisp_Value_alloc(state, state->Symbol);
    lisp_List_mut_set((lisp_List*) value->values->data, 0, lisp_String_from_ascii(state, ascii));
    return value;
}

static void lisp_Symbol_boot(lisp_State* state) {
    lisp_Value* Symbol = state->Symbol;
    lisp_List* attributes = (lisp_List*) lisp_List_get(state, (lisp_List*) Symbol->values->data, LISP_IDX_TYPE_ATTRIBUTES)->data;
    lisp_List_mut_set(attributes, 0, lisp_Symbol_from_ascii(state, "string"));
}


#endif
