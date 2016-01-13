#ifndef __LISP_LANG_CHARACER_C__
#define __LISP_LANG_CHARACER_C__


inline static lisp_Character* lisp_Character_u8(lisp_Character* character, lisp_u8 ch) {
    lisp_u8* bytes = (lisp_u8*) malloc(sizeof(lisp_u8));
    bytes[0] = ch;
    character->bytes = bytes;
    character->size = 1;
    return character;
}

inline static lisp_Character* lisp_Character_bytes(lisp_Character* character, lisp_u8* bytes, lisp_u8 size) {
    character->bytes = bytes;
    character->size = size;
    return character;
}

inline static void lisp_Character_delete(lisp_Character* character) {
    free(character->bytes);
}

inline static lisp_u8 lisp_Character_to_char(lisp_Character* character) {
    return character->bytes[0];
}

inline static struct lisp_Value* lisp_Character_to_string(lisp_State* state, lisp_Character* character) {
    return lisp_Value_cstring(state, character->bytes);
}


#endif
