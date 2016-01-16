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

static lisp_u8 lisp_Reader_index(lisp_Reader* reader, lisp_u64 index) {
    return reader->cstring[(reader->index + index)];
}

static lisp_i64 lisp_Reader_index_of(lisp_u8* cstring, lisp_u8 ch) {
    lisp_u64 index = 0;
    lisp_u8 c = cstring[index];

    while (c != '\0') {
        if (c == ch) {
            return index;
        }
        index = index + 1;
        c = cstring[index];
    }

    return -1;
}

static lisp_u8 lisp_Reader_read(lisp_Reader* reader) {
    lisp_u64 index = reader->index;
    lisp_u8 ch = reader->cstring[index];

    if (ch != '\0') {
        reader->index = index + 1;
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

static lisp_u64 lisp_Reader_next_whitespace(lisp_Reader* reader, lisp_u8 ch) {
    lisp_u64 size = 0;

    while (ch != '\0' && !lisp_Reader_is_whitespace(ch) && !lisp_Reader_is_marco(ch)) {
        ch = lisp_Reader_index(reader, size);
        size = size + 1;
    }

    return size;
}

static lisp_u8* lisp_Reader_next_token(lisp_Reader* reader, lisp_u8 ch) {
    lisp_u64 size = lisp_Reader_next_whitespace(reader, ch);
    lisp_u8* token = (lisp_u8*) malloc((size + 1) * sizeof(lisp_u8));

    token[0] = ch;
    for (lisp_u64 i = 1, il = size; i < il && ch != '\0'; i++) {
        ch = lisp_Reader_read(reader);
        token[i] = ch;
    }
    token[size] = '\0';

    return token;
}

static lisp_u8* lisp_Reader_next_number(lisp_Reader* reader, lisp_u8 ch) {
    lisp_u64 size = 0;

    while (LISP_TRUE) {
        lisp_u8 c = lisp_Reader_index(reader, size);
        if (c == '\0' || lisp_Reader_is_whitespace(c) || lisp_Reader_is_marco(c)) {
            break;
        }
        size += 1;
    }

    size += 1;
    lisp_u8* token = (lisp_u8*) malloc((size + 1) * sizeof(lisp_u8));

    token[0] = ch;
    for (lisp_u64 i = 1, il = size; i < il && ch != '\0'; i++) {
        ch = lisp_Reader_read(reader);
        token[i] = ch;
    }
    token[size] = '\0';

    return token;
}

static lisp_Value* lisp_Reader_next(lisp_Reader* reader, lisp_u8 return_on_char) {
    while (LISP_TRUE) {
        lisp_u8 ch = lisp_Reader_read(reader);

        while (ch != '\0' && lisp_Reader_is_whitespace(ch)) {
            ch = lisp_Reader_read(reader);
        }

        if (ch == '\0' || ch == return_on_char) {
            return NULL;
        }

        if (lisp_Reader_is_numeric(ch)) {
            return lisp_Reader_read_number(reader, ch);
        }
        if (ch == '(') {
            return lisp_Reader_read_list(reader, ch);
        }

        return lisp_Reader_read_token(reader, ch);
    }
}

static lisp_Value* lisp_Reader_read_number(lisp_Reader* reader, lisp_u8 ch) {
    lisp_u8* cstring = lisp_Reader_next_number(reader, ch);
    lisp_Value* value;

    if (lisp_Reader_index_of(cstring, '.') != -1) {
        value = lisp_Value_number_from_f64(reader->state, lisp_atod(cstring));
    } else {
        value = lisp_Value_number_from_i32(reader->state, lisp_atoi(cstring));
    }
    free(cstring);

    return value;
}

static lisp_Value* lisp_Reader_read_list(lisp_Reader* reader, lisp_u8 ch) {
    lisp_Array* array = lisp_Array_new();
    lisp_Value* value = lisp_Reader_next(reader, ')');

    while (value != NULL) {
        lisp_Array_push(array, value);
        value = lisp_Reader_next(reader, ')');
    }

    lisp_Value* list = lisp_Value_list_from_array(reader->state, array);
    lisp_Array_delete(array);

    return list;
}

static lisp_Value* lisp_Reader_read_token(lisp_Reader* reader, lisp_u8 ch) {
    lisp_Value* value;
    lisp_u8* cstring = lisp_Reader_next_token(reader, ch);

    if (lisp_cstring_equal(cstring, "true")) {
        value = lisp_Value_boolean(reader->state, 1);
    } else if (lisp_cstring_equal(cstring, "false")) {
        value = lisp_Value_boolean(reader->state, 0);
    } else {
        value = lisp_Value_symbol_from_cstring(reader->state, cstring);
    }
    free(cstring);
    
    return value;
}



#endif
