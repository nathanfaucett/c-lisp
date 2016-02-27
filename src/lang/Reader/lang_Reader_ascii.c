#ifndef __LISP_LANG_READER_ASCII_C__
#define __LISP_LANG_READER_ASCII_C__


static char lisp_Reader_ascii_index(lisp_Object* reader, char* ascii, uintsize index) {
    uintsize i = LISP_OBJECT_GET_DATA(((lisp_Object**) reader->data)[LISP_IDX_READER_INDEX], uintsize);
    return ascii[i + index];
}
static uintsize lisp_Reader_ascii_next_whitespace(lisp_Object* reader, char* ascii, char ch) {
    uintsize size = 0;

    while (ch != '\0' && !lisp_is_whitespace(ch) && ch != ',' && !lisp_Reader_is_marco(ch)) {
        ch = lisp_Reader_ascii_index(reader, ascii, size);
        size = size + 1;
    }

    return size;
}
static char* lisp_Reader_ascii_next_token(lisp_State* state, lisp_Object* reader, char* ascii, char ch) {
    uintsize size = lisp_Reader_ascii_next_whitespace(reader, ascii, ch);
    char* token = (char*) malloc((size + 1) * sizeof(char));

    token[0] = ch;
    uintsize i = 1, il = size;
    for (; i < il && ch != '\0'; i++) {
        token[i] = lisp_Reader_ascii_read(state, reader, ascii);
    }
    token[size] = '\0';

    return token;
}
static char* lisp_Reader_ascii_next_number(lisp_State* state, lisp_Object* reader, char* ascii, char ch) {
    uintsize size = 0;
    char c;

    while (true) {
        c = lisp_Reader_ascii_index(reader, ascii, size);
        if (!(lisp_is_numeric(c) || c == '.')) {
            break;
        }
        size += 1;
    }
    size += 1;

    char* token = (char*) malloc((size + 1) * sizeof(char));

    token[0] = ch;
    uintsize i = 1, il = size;
    for (; i < il && ch != '\0'; i++) {
        token[i] = lisp_Reader_ascii_read(state, reader, ascii);
    }
    token[size] = '\0';

    return token;
}
static char lisp_Reader_ascii_read(lisp_State* state, lisp_Object* reader, char* ascii) {
    lisp_Object** values = (lisp_Object**) reader->data;
    uintsize index = LISP_OBJECT_GET_DATA(values[LISP_IDX_READER_INDEX], uintsize);
    char ch = ascii[index];

    if (ch != '\0') {
        values[LISP_IDX_READER_INDEX] = lisp_Number_new_UInt(state, index + 1);
    }
    if (ch == '\n' || ch == '\r') {
        values[LISP_IDX_READER_LAST_COLUMN] = values[LISP_IDX_READER_COLUMN];
        uintsize row = LISP_OBJECT_GET_DATA(values[LISP_IDX_READER_ROW], uintsize);
        values[LISP_IDX_READER_ROW] = lisp_Number_new_UInt(state, row + 1);
        values[LISP_IDX_READER_COLUMN] = lisp_Number_new_UInt(state, 1);
    } else {
        uintsize column = LISP_OBJECT_GET_DATA(values[LISP_IDX_READER_COLUMN], uintsize);
        values[LISP_IDX_READER_COLUMN] = lisp_Number_new_UInt(state, column + 1);
    }

    return ch;
}
static char lisp_Reader_ascii_unread(lisp_State* state, lisp_Object* reader, char* ascii) {
    lisp_Object** values = (lisp_Object**) reader->data;
    uintsize index = LISP_OBJECT_GET_DATA(values[LISP_IDX_READER_INDEX], uintsize);

    if (index != 0) {
        values[LISP_IDX_READER_INDEX] = lisp_Number_new_UInt(state, index - 1);
        char ch = ascii[index - 1];

        if (ch == '\n' || ch == '\r') {
            uintsize row = LISP_OBJECT_GET_DATA(values[LISP_IDX_READER_ROW], uintsize);
            values[LISP_IDX_READER_ROW] = lisp_Number_new_UInt(state, row - 1);
            values[LISP_IDX_READER_COLUMN] = values[LISP_IDX_READER_LAST_COLUMN];
        } else {
            uintsize column = LISP_OBJECT_GET_DATA(values[LISP_IDX_READER_COLUMN], uintsize);
            values[LISP_IDX_READER_COLUMN] = lisp_Number_new_UInt(state, column - 1);
        }

        return ch;
    } else {
        return ascii[index];
    }
}

lisp_Object* lisp_Reader_ascii_next(lisp_State* state, lisp_Object* reader, char* ascii, char return_on) {
    char ch;

    while (true) {
        ch = lisp_Reader_ascii_read(state, reader, ascii);

        while (lisp_is_whitespace(ch) || ch == ',') {
            ch = lisp_Reader_ascii_read(state, reader, ascii);
        }

        if (ch == '\0' || ch == return_on) {
            return NULL;
        }
        if (ch == ')' || ch == ']' || ch == '}') {
            return NULL;
        }

        if (lisp_is_numeric(ch) || (ch == '-' && lisp_is_numeric(lisp_Reader_ascii_index(reader, ascii, 0)))) {
            return lisp_Reader_ascii_read_number(state, reader, ascii, ch);
        }
        if (ch == '(') {
            return lisp_Reader_ascii_read_list(state, reader, ascii, ch);
        }
        if (ch == '[') {
            return lisp_Reader_ascii_read_vector(state, reader, ascii, ch);
        }
        if (ch == '{') {
            return lisp_Reader_ascii_read_map(state, reader, ascii, ch);
        }
        if (ch == '"') {
            return lisp_Reader_ascii_read_string(state, reader, ascii, ch);
        }
        if (ch == '\'') {
            return lisp_Reader_ascii_read_char(state, reader, ascii, ch);
        }

        if (ch == ';') {
            lisp_Reader_ascii_read_comment(state, reader, ascii, ch);
        } else {
            return lisp_Reader_ascii_read_token(state, reader, ascii, ch);
        }
    }
}

static lisp_Object* lisp_Reader_ascii_read_number(lisp_State* state, lisp_Object* reader, char* ascii, char ch) {
    char* cstring = lisp_Reader_ascii_next_number(state, reader, ascii, ch);
    lisp_Object* object;

    if (lisp_ascii_index_of(cstring, '.') != 0) {
        object = lisp_Object_alloc(state, state->Float64);
        LISP_OBJECT_SET_DATA(object, float64, string_to_float64(cstring));
    } else {
        if (cstring[0] == '-') {
            object = lisp_Object_alloc(state, state->Int);
            LISP_OBJECT_SET_DATA(object, uintsize, string_to_intsize(cstring));
        } else {
            object = lisp_Object_alloc(state, state->UInt);
            LISP_OBJECT_SET_DATA(object, uintsize, string_to_uintsize(cstring));
        }
    }
    free(cstring);

    return object;
}

static lisp_Object* lisp_Reader_ascii_read_list(lisp_State* state, lisp_Object* reader, char* ascii, char ch) {
    lisp_Object* list = lisp_List_new_type(state, state->AnyList);
    lisp_Object* object = lisp_Reader_ascii_next(state, reader, ascii, ')');

    while (object != NULL) {
        lisp_List_mut_push(state, list, object);
        object = lisp_Reader_ascii_next(state, reader, ascii, ')');
    }

    return list;
}
static lisp_Object* lisp_Reader_ascii_read_vector(lisp_State* state, lisp_Object* reader, char* ascii, char ch) {
    lisp_Object* vector = lisp_Vector_new_type(state, state->AnyVector);
    lisp_Object* object = lisp_Reader_ascii_next(state, reader, ascii, ']');

    while (object != NULL) {
        lisp_Vector_mut_push(state, vector, object);
        object = lisp_Reader_ascii_next(state, reader, ascii, ']');
    }

    return vector;
}
static lisp_Object* lisp_Reader_ascii_read_map(lisp_State* state, lisp_Object* reader, char* ascii, char ch) {
    lisp_Object* map = lisp_Map_new_type(state, state->AnyAnyMap);
    lisp_Object* key;
    lisp_Object* value;

    while (true) {
        key = lisp_Reader_ascii_next(state, reader, ascii, '}');
        if (key != NULL) {
            value = lisp_Reader_ascii_next(state, reader, ascii, '}');
        } else {
            break;
        }
        lisp_Map_mut_set(state, map, key, value);
    }

    return map;
}

static lisp_Object* lisp_Reader_ascii_read_string(lisp_State* state, lisp_Object* reader, char* ascii, char ch) {
    lisp_Object* string = lisp_Vector_new_type(state, state->CharVector);
    lisp_Object* ch_object;

    ch = lisp_Reader_ascii_read(state, reader, ascii);

    /* fixme: parse utf-8 chars */
    while (ch != '\0' && ch != '"') {
        ch_object = lisp_Object_alloc(state, state->Char);
        LISP_OBJECT_SET_DATA(ch_object, uint32, ch);

        lisp_Vector_mut_push(state, string, ch_object);

        ch = lisp_Reader_ascii_read(state, reader, ascii);
    }

    return string;
}

static lisp_Object* lisp_Reader_ascii_read_char(lisp_State* state, lisp_Object* reader, char* ascii, char ch) {
    lisp_Object* ch_object = lisp_Object_alloc(state, state->Char);

    ch = lisp_Reader_ascii_read(state, reader, ascii);

    do {
        /* fixme: parse utf-8 chars */
        LISP_OBJECT_SET_DATA(ch_object, uint32, ch);
        ch = lisp_Reader_ascii_read(state, reader, ascii);
    } while (ch != '\0' && ch != '\'');

    return ch_object;
}

static void lisp_Reader_ascii_read_comment(lisp_State* state, lisp_Object* reader, char* ascii, char ch) {
    do {
        ch = lisp_Reader_ascii_read(state, reader, ascii);
    } while (ch != '\0' && ch != '\n' && ch != '\r');
}

static lisp_Object* lisp_Reader_ascii_read_token(lisp_State* state, lisp_Object* reader, char* ascii, char ch) {
    char* cstring = lisp_Reader_ascii_next_token(state, reader, ascii, ch);
    lisp_Object* value;

    if (lisp_cstring_equal(cstring, "true")) {
        value = state->tru;
    } else if (lisp_cstring_equal(cstring, "false")) {
        value = state->fal;
    } else if (lisp_cstring_equal(cstring, "nil")) {
        value = state->nil;
    } else if (cstring[0] == ':') {
        value = lisp_Keyword_from_ascii(state, cstring);
    } else {
        value = lisp_Symbol_from_ascii(state, cstring);
    }
    free(cstring);

    return value;
}


#endif
