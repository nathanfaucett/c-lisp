#ifndef __LISP_LANG_SYMBOL_C__
#define __LISP_LANG_SYMBOL_C__


lisp_Object* lisp_Symbol_from_ascii(lisp_State* state, char* ascii) {
    lisp_Object* object = lisp_boot_object_size(state, state->Symbol, sizeof(void*));
    ((lisp_Object**) object->data)[LISP_IDX_SYMBOL_STRING] = lisp_Vector_from_ascii(state, ascii);
    return object;
}


#endif
