#ifndef __LISP_LANG_STRING_C__
#define __LISP_LANG_STRING_C__


static void lisp_String_alloc(lisp_State* state, lisp_Object* object) {
    lisp_String* string = (lisp_String*) object->data;
    string->chars = NULL;
    string->size = 0;
}
static void lisp_String_mark(lisp_Object* object) {
    lisp_String* string = (lisp_String*) object->data;

    if (string->chars != NULL) {
        lisp_size i = 0, il = string->size;
        for (; i < il; i++) {
            lisp_Object_mark(string->chars[i]);
        }
    }
}

static lisp_Object* lisp_String_from_ascii(lisp_State* state, lisp_char* ascii) {
    lisp_Object* object = lisp_Object_alloc(state, state->String);
    lisp_String* string = (lisp_String*) object->data;

    lisp_size size = lisp_ascii_size(ascii);
    lisp_Object** chars = (lisp_Object**) lisp_State_assoc(state, object->gc_node, size * sizeof(lisp_Object*));

    lisp_size i = 0, il = size;
    for (; i < il; i++) {
        lisp_Object* object = lisp_Object_alloc(state, state->Char);
        LISP_SET_DATA(object, lisp_u32, ascii[i]);
        chars[i] = object;
    }

    string->chars = chars;
    string->size = size;

    return object;
}
static lisp_char* lisp_String_to_ascii(lisp_String* string) {
    lisp_char* ascii = (lisp_char*) malloc((string->size + 1) * sizeof(lisp_char));

    lisp_size i = 0, il = string->size;
    for (; i < il; i++) {
        ascii[i] = (lisp_char) *((lisp_u32*) string->chars[i]->data);
    }
    ascii[string->size] = '\0';

    return ascii;
}


#endif
