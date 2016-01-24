#ifndef __LISP_LANG_CHAR_C__
#define __LISP_LANG_CHAR_C__


static void lisp_Char_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Char* ch = (lisp_Char*) lisp_State_alloc(state, sizeof(lisp_Char));
    value->value = ch;
    ch->bytes[0] = '\0';
    ch->size = 1;
}
static void lisp_Char_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_State_dealloc(state, value->value);
}

static void lisp_Char_from_ascii(lisp_Char* ch, lisp_char i8) {
    ch->bytes[0] = i8;
    ch->size = 1;
}
static lisp_u64 lisp_Char_from_utf8(lisp_Char* ch, lisp_u32* cstring, lisp_u64 start) {
    lisp_u8 size = 1;
    lisp_u64 i = start;

    if (cstring[i] != '\0') {
        if ((cstring[0] & lisp_Char_mask[0]) == lisp_Char_mask[0]) {
            size += 1;
        }
        if ((cstring[0] & lisp_Char_mask[1]) == lisp_Char_mask[1]) {
            size += 1;
        }
        if ((cstring[0] & lisp_Char_mask[2]) == lisp_Char_mask[2]) {
            size += 1;
        }

        lisp_u16 j = 0;
        while (j < size) {
            ch->bytes[j] = cstring[i + j];
            j += 1;
        }

        ch->size = size;

        return i + size;
    } else {
        ch->bytes[0] = '\0';
        ch->size = 1;
        return 0;
    }
}

static lisp_u64 lisp_Char_to_u32(lisp_Char* ch) {
    lisp_u64 c = 0;
    for (lisp_u8 i = 0, il = ch->size; i < il; i++) {
        c += ch->bytes[i];
    }
    return c;
}
static lisp_char lisp_Char_to_char(lisp_Char* ch) {
    return ch->bytes[0];
}


#endif
