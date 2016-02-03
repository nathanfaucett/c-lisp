#ifndef __LISP_LANG_STRING_C__
#define __LISP_LANG_STRING_C__


static void lisp_String_alloc(lisp_State* state, lisp_Value* value) {
    lisp_String* string = (lisp_String*) value->data;
    string->chars = NULL;
    string->size = 0;
}
static void lisp_String_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_String* string = (lisp_String*) value->data;

    if (string->chars != NULL) {
        lisp_State_dealloc(state, string->chars);
    }
}
static void lisp_String_mark(lisp_Value* value) {
    lisp_String* string = (lisp_String*) value->data;

    if (string->chars != NULL) {
        lisp_size i = 0, il = string->size;
        for (; i < il; i++) {
            lisp_Value_mark(string->chars[i]);
        }
    }
}

static lisp_Value* lisp_String_from_ascii(lisp_State* state, lisp_char* ascii) {
    lisp_Value* value = lisp_Value_alloc(state, state->String);
    lisp_String* string = (lisp_String*) value->data;

    lisp_size size = lisp_ascii_size(ascii);
    lisp_Value** chars = (lisp_Value**) lisp_State_alloc(state, size * sizeof(lisp_Value*));

    lisp_size i = 0, il = size;
    for (; i < il; i++) {
        lisp_Value* value = lisp_Value_alloc(state, state->Char);
        LISP_SET_DATA(value, lisp_u32, ascii[i]);
        chars[i] = value;
    }

    string->chars = chars;
    string->size = size;

    return value;
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

static void lisp_String_boot(lisp_State* state) {
    /* lisp_Value* String = state->String; */
}


#endif
