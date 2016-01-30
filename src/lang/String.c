#ifndef __LISP_LANG_STRING_C__
#define __LISP_LANG_STRING_C__


static void lisp_String_alloc(lisp_State* state, lisp_Value* value) {
    lisp_String* string = (lisp_String*) value->data;
    string->chars = NULL;
    string->size = 0;
}
static void lisp_String_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_String* string = (lisp_String*) value->data;
    free(string->chars);
}
static void lisp_String_mark(lisp_Value* value) {
    lisp_String* string = (lisp_String*) value->data;

    if (string->chars != NULL) {
        for (lisp_size i = 0, il = string->size; i < il; i++) {
            lisp_Value_mark(string->chars[i]);
        }
    }
}

static lisp_Value* lisp_String_new_ascii(lisp_State* state, lisp_char* ascii) {
    lisp_Value* value = lisp_Value_alloc(state, state->String);
    lisp_String* string = (lisp_String*) value->data;

    lisp_size size = lisp_ascii_size(ascii);
    lisp_Value** chars = (lisp_Value**) malloc(size * sizeof(lisp_Value*));

    for (lisp_size i = 0, il = size; i < il; i++) {
        lisp_Value* value = lisp_Value_alloc(state, state->Char);
        LISP_SET_BITS(value, lisp_u32, ascii[i]);
        chars[i] = value;
    }

    string->chars = chars;
    string->size = size;

    return value;
}

static lisp_bool lisp_String_equal(lisp_String* a, lisp_String* b) {
    if (a == b) {
        return LISP_TRUE;
    } else if (a->size != b->size) {
        return LISP_FALSE;
    } else {
        for (lisp_size i = 0, il = a->size; i < il; i++) {
            lisp_u32 ach = *((lisp_u32*) a->chars[i]->data);
            lisp_u32 bch = *((lisp_u32*) b->chars[i]->data);

            if (ach != bch) {
                return LISP_FALSE;
            }
        }
        return LISP_TRUE;
    }
}


#endif
