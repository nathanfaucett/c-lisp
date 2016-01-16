#ifndef __LISP_CORE_READER_C__
#define __LISP_CORE_READER_C__


static lisp_Reader* lisp_Reader_constructor(lisp_Reader* reader, lisp_State* state, lisp_u8* cstring) {
    reader->state = state;
    reader->cstring = cstring;
    reader->index = 0;
    reader->column = 1;
    reader->row = 1;
    return reader;
}

static lisp_Reader* lisp_Reader_new(lisp_State* state, lisp_u8* cstring) {
    return lisp_Reader_constructor(
        (lisp_Reader*) malloc(sizeof(lisp_Reader)),
        state,
        cstring
    );
}

static void lisp_Reader_delete(lisp_Reader* reader) {
    free(reader);
}

static lisp_bool lisp_Reader_is_whitespace(lisp_u8 ch) {
    lisp_u32 code = (lisp_u32) ch;
    return (
        (code >= 0x0009 && code <= 0x000D) ||
        code == 0x0020 ||
        code == 0x0085 ||
        code == 0x00A0 ||
        code == 0x2028 ||
        code == 0x2029
    );
}

static lisp_bool lisp_Reader_is_numeric(lisp_u8 ch) {
    lisp_u32 code = (lisp_u32) ch;
    return code >= 0x30 && code <= 0x39;
}

static lisp_bool lisp_Reader_is_marco(lisp_u8 ch) {
    return (
        ch == '"' ||
        ch == '\'' ||
        ch == ';' ||
        ch == '(' ||
        ch == ')' ||
        ch == '[' ||
        ch == ']' ||
        ch == '{' ||
        ch == '}'
    );
}

static lisp_u8 lisp_Reader_read(lisp_Reader* reader) {
    lisp_u64 index = reader->index;
    lisp_u8 ch;

    if (index != 0) {
        index += 1;
        ch = reader->cstring[index];
    } else {
        ch = reader->cstring[index];
        index += 1;
    }

    if (ch != '\0') {
        reader->index = index;
    }

    return ch;
}

static lisp_u8 lisp_Reader_unread(lisp_Reader* reader) {
    lisp_u64 index = 0;

    if (reader->index != 0) {
        reader->index -= 1;
        index = reader->index;
    }

    return reader->cstring[index];
}

static lisp_Value* lisp_Reader_next(lisp_Reader* reader) {
    while (LISP_TRUE) {
        lisp_u8 ch = lisp_Reader_read(reader);

        while (ch != '\0' && lisp_Reader_is_whitespace(ch)) {
            ch = lisp_Reader_read(reader);
        }

        if (ch == '\0') {
            return NULL;
        }

        if (lisp_Reader_is_numeric(ch)) {
            return lisp_Reader_read_number(reader, ch);
        }
    }
}

static lisp_Value* lisp_Reader_read_number(lisp_Reader* reader, lisp_u8 ch) {
    while (LISP_TRUE) {
        lisp_u8 ch = lisp_Reader_read(reader);

        if (ch == '\0' || lisp_Reader_is_whitespace(ch) || lisp_Reader_is_marco(ch)) {
            lisp_Reader_unread(reader);
            break;
        }
    }

    return lisp_Value_number_from_f64(reader->state, 0.0);
}



#endif
