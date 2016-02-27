#ifndef __LISP_LANG_KEYWORD_C__
#define __LISP_LANG_KEYWORD_C__


lisp_Object* lisp_Keyword_from_ascii(lisp_State* state, char* ascii) {
    lisp_Object* object = lisp_boot_object_size(state, state->Keyword, sizeof(void*));
    ((lisp_Object**) object->data)[LISP_IDX_KEYWORD_STRING] = lisp_Vector_from_ascii(state, ascii);
    return object;
}


#endif
