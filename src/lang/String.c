#ifndef __LISP_LANG_STRING_C__
#define __LISP_LANG_STRING_C__


static void lisp_String_destructor(lisp_State* state, lisp_String* string) {
    for (lisp_u32 i = 0, il = string->size; i < il; i++) {
        lisp_Value_deref(state, string->chars[i]->value);
    }
}

static lisp_String* lisp_String_from_cstring(lisp_State* state, lisp_String* string, lisp_u8* cstring) {
    lisp_u32 size = lisp_cstring_size(cstring);
    lisp_Character** chars = (lisp_Character**) malloc(size * sizeof(lisp_Character*));

    lisp_u32 index = 0;
    lisp_u8 ch = cstring[index];

    while (ch != '\0') {
        lisp_Value* value = lisp_Value_character_from_ch(state, ch);
        chars[index] = &value->character;
        index += 1;
        ch = cstring[index];
    }

    string->chars = chars;
    string->size = size;

    return string;
}

static lisp_Value* lisp_String_concat(lisp_State* state, lisp_String* a, lisp_String* b) {
    lisp_Value* value = lisp_State_alloc(state);
    lisp_u32 size = a->size + b->size;
    lisp_Character** chars = (lisp_Character**) malloc(size * sizeof(lisp_Character*));

    for (lisp_u32 i = 0, il = a->size; i < il; i++) {
        lisp_Character* ch = a->chars[i];
        lisp_Value_ref(ch->value);
        chars[i] = ch;
    }
    for (lisp_u32 j = a->size, jl = size, k = 0; j < jl; j++, k++) {
        lisp_Character* ch = b->chars[k];
        lisp_Value_ref(ch->value);
        chars[j] = ch;
    }

    value->string.chars = chars;
    value->string.size = size;

    return value;
}

static lisp_u8* lisp_String_to_cstring(lisp_String* string) {
    lisp_u8* cstring = (lisp_u8*) malloc((string->size + 1) * sizeof(lisp_u8));

    for (lisp_u32 i = 0, il = string->size; i < il; i++) {
        cstring[i] = lisp_Character_to_char(string->chars[i]);
    }
    cstring[string->size] = '\0';

    return cstring;
}

static lisp_bool lisp_String_equal(lisp_String* a, lisp_String* b) {
    if (a == b) {
        return LISP_TRUE;
    } else if (a->size != b->size) {
        return LISP_FALSE;
    } else {
        for (lisp_u32 i = 0, il = a->size; i < il; i++) {
            if (!lisp_Character_equal(a->chars[i], b->chars[i])) {
                return LISP_FALSE;
            }
        }
        return LISP_TRUE;
    }
}


#endif
