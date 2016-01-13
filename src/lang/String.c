#ifndef __LISP_LANG_STRING_C__
#define __LISP_LANG_STRING_C__


inline static lisp_String* lisp_String_cstring(lisp_State* state, lisp_String* string, lisp_u8* cstring) {
    lisp_u32 size = str_size(cstring);
    lisp_Character** chars = (lisp_Character**) malloc(size * sizeof(lisp_Character*));

    lisp_u32 index = 0;
    lisp_u8 ch = cstring[index];

    while (ch != '\0') {
        lisp_Value* value = lisp_Value_ch(state, ch);
        lisp_Value_ref(value);
        chars[index] = &value->character;
        index += 1;
        ch = cstring[index];
    }

    string->chars = chars;
    string->size = size;

    return string;
}

inline static void lisp_String_delete(lisp_State* state, lisp_String* string) {
    for (lisp_u32 i = 0, il = string->size; i < il; i++) {
        lisp_Value_deref(state, string->chars[i]->value);
    }
}

inline static lisp_Value* lisp_String_concat(lisp_State* state, lisp_String* a, lisp_String* b) {
    lisp_Value* value = lisp_State_alloc(state);
    lisp_u32 size = a->size + b->size;
    lisp_Character** chars = (lisp_Character**) malloc(size * sizeof(lisp_Character*));

    for (lisp_u32 i = 0, il = a->size; i < il; i++) {
        lisp_Character* ch = a->chars[i];
        lisp_Value_ref(ch->value);
        chars[i] = ch;
    }
    for (lisp_u32 i = a->size, il = size, j = 0; i < il; i++, j++) {
        lisp_Character* ch = b->chars[j];
        lisp_Value_ref(ch->value);
        chars[i] = ch;
    }

    value->string.chars = chars;
    value->string.size = size;

    return value;
}

inline static lisp_u8* lisp_String_to_cstring(lisp_String* string) {
    lisp_u8* cstring = (lisp_u8*) malloc((string->size + 1) * sizeof(lisp_u8));

    for (lisp_u32 i = 0, il = string->size; i < il; i++) {
        cstring[i] = lisp_Character_to_char(string->chars[i]);
    }
    cstring[string->size] = '\0';

    return cstring;
}


#endif
