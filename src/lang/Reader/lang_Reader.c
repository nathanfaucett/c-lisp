#ifndef __LISP_LANG_READER_C__
#define __LISP_LANG_READER_C__


static bool lisp_is_whitespace(uint32 ch) {
    return (
        (ch >= 0x0009 && ch <= 0x000D) ||
        ch == 0x0020 ||
        ch == 0x0085 ||
        ch == 0x00A0 ||
        ch == 0x2028 ||
        ch == 0x2029
    );
}
static bool lisp_is_numeric(uint32 ch) {
    return ch >= 0x30 && ch <= 0x39;
}
static uint32 lisp_escape(uint32 ch) {
    switch ((char) ch) {
        case 't':
            return '\t';
        case 'r':
            return '\r';
        case 'n':
            return '\n';
        case 'b':
            return '\b';
        case 'f':
            return '\f';
        default:
            return ch;
    }
}
static uintsize lisp_ascii_index_of(char* ascii, char ch) {
    uintsize index = 0;
    char c = ascii[index];

    while (c != '\0') {
        if (ch == c) {
            return index + 1;
        }
        index += 1;
        c = ascii[index];
    }

    return 0;
}
static bool lisp_cstring_equal(char* a, char* b) {
    uintsize index = 0;
    char ach = a[index];
    char bch = b[index];

    while (ach != '\0' && bch != '\0') {
        if (ach != bch) {
            return false;
        }
        index += 1;
        ach = a[index];
        bch = b[index];
    }

    return true;
}

lisp_Object* lisp_Reader_new(lisp_State* state) {
    lisp_Object* reader = lisp_boot_object_size(state, state->Reader, 4 * sizeof(void*));
    lisp_Object** values = (lisp_Object**) reader->data;
    values[LISP_IDX_READER_INDEX] = lisp_Number_new_UInt(state, 0);
    values[LISP_IDX_READER_COLUMN] = lisp_Number_new_UInt(state, 1);
    values[LISP_IDX_READER_ROW] = lisp_Number_new_UInt(state, 1);
    values[LISP_IDX_READER_LAST_COLUMN] = lisp_Number_new_UInt(state, 1);
    return reader;
}
static bool lisp_Reader_is_marco(uint32 ch) {
    char c = (char) ch;
    return (
        c == '"' ||
        c == '\'' ||
        c == ';' ||
        c == '(' ||
        c == ')' ||
        c == '[' ||
        c == ']' ||
        c == '{' ||
        c == '}'
    );
}


#endif
