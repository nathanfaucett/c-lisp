#ifndef __LISP_CORE_READER_C__
#define __LISP_CORE_READER_C__


static lisp_Reader* lisp_Reader_constructor(lisp_Reader* reader, lisp_State* state, lisp_char* cstring, FILE* file) {
    reader->state = state;
    reader->cstring = cstring;
    reader->file = file;
    reader->index = 0;
    reader->column = 1;
    reader->row = 1;
    return reader;
}

static lisp_Reader* lisp_Reader_from_cstring(lisp_State* state, lisp_char* cstring) {
    return lisp_Reader_constructor(
        (lisp_Reader*) malloc(sizeof(lisp_Reader)),
        state,
        cstring,
        NULL
    );
}
static lisp_Reader* lisp_Reader_from_file(lisp_State* state, FILE* file) {
    return lisp_Reader_constructor(
        (lisp_Reader*) malloc(sizeof(lisp_Reader)),
        state,
        NULL,
        file
    );
}

static void lisp_Reader_delete(lisp_Reader* reader) {
    free(reader);
}

static lisp_bool lisp_Reader_is_marco(lisp_u32 ch) {
    lisp_char c = (lisp_char) ch;

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

static lisp_u32 lisp_Reader_index(lisp_Reader* reader, lisp_u64 index) {
    return reader->cstring[(reader->index + index)];
}

static lisp_u32 lisp_Reader_read(lisp_Reader* reader) {
    lisp_u64 index = reader->index;
    lisp_u32 ch = reader->cstring[index];

    if (ch != '\0') {
        reader->index = index + 1;
    }

    return ch;
}

static lisp_u32 lisp_Reader_unread(lisp_Reader* reader) {
    if (reader->index != 0) {
        reader->index -= 1;
    }
    return reader->cstring[reader->index];
}

static lisp_u64 lisp_Reader_next_whitespace(lisp_Reader* reader, lisp_u32 ch) {
    lisp_u64 size = 0;

    while (ch != '\0' && !lisp_is_whitespace(ch) && !lisp_Reader_is_marco(ch)) {
        ch = lisp_Reader_index(reader, size);
        size = size + 1;
    }

    return size;
}

static lisp_u32* lisp_Reader_next_token(lisp_Reader* reader, lisp_u32 ch) {
    lisp_u64 size = lisp_Reader_next_whitespace(reader, ch);
    lisp_u32* token = (lisp_u32*) malloc((size + 1) * sizeof(lisp_u32));

    token[0] = ch;
    for (lisp_u64 i = 1, il = size; i < il && ch != '\0'; i++) {
        ch = lisp_Reader_read(reader);
        token[i] = ch;
    }
    token[size] = '\0';

    return token;
}

static lisp_char* lisp_Reader_next_number(lisp_Reader* reader, lisp_u32 ch) {
    lisp_u64 size = 0;

    while (LISP_TRUE) {
        lisp_char c = lisp_Reader_index(reader, size);
        if (c == '\0' || lisp_is_whitespace(c) || lisp_Reader_is_marco(c)) {
            break;
        }
        size += 1;
    }

    size += 1;
    lisp_char* token = (lisp_char*) malloc((size + 1) * sizeof(lisp_char));

    token[0] = ch;
    for (lisp_u64 i = 1, il = size; i < il && ch != '\0'; i++) {
        ch = lisp_Reader_read(reader);
        token[i] = ch;
    }
    token[size] = '\0';

    return token;
}

static lisp_Value* lisp_Reader_next(lisp_Reader* reader, lisp_u32 return_on_char) {
    while (LISP_TRUE) {
        lisp_u32 ch = lisp_Reader_read(reader);

        while (ch != '\0' && lisp_is_whitespace(ch)) {
            ch = lisp_Reader_read(reader);
        }

        if (ch == '\0' || ch == return_on_char) {
            return NULL;
        }

        if (lisp_is_numeric(ch)) {
            return lisp_Reader_read_number(reader, ch);
        }
        if (ch == '(') {
            return lisp_Reader_read_list(reader, ch);
        }
        if (ch == '[') {
            return lisp_Reader_read_vector(reader, ch);
        }
        if (ch == '{') {
            return lisp_Reader_read_map(reader, ch);
        }
        if (ch == '"') {
            return lisp_Reader_read_string(reader, ch);
        }
        if (ch == '\'') {
            return lisp_Reader_read_character(reader, ch);
        }

        if (ch == ';') {
            lisp_Reader_read_comment(reader, ch);
        } else {
            return lisp_Reader_read_token(reader, ch);
        }
    }
}

static lisp_Value* lisp_Reader_read_number(lisp_Reader* reader, lisp_u32 ch) {
    lisp_char* cstring = lisp_Reader_next_number(reader, ch);
    lisp_Value* value;

    if (lisp_cstring_index_of(cstring, '.') != -1) {
        /* fixme */
        value = lisp_Value_alloc(reader->state, reader->state->type_int64);
        ((lisp_Int64*) value->value)->value = lisp_cstring_to_f64(cstring);
    } else {
        value = lisp_Value_alloc(reader->state, reader->state->type_int64);
        ((lisp_Int64*) value->value)->value = lisp_cstring_to_i64(cstring);
    }
    free(cstring);

    return value;
}

static lisp_Value* lisp_Reader_read_list(lisp_Reader* reader, lisp_u32 ch) {
    lisp_MutList* mut_list = lisp_MutList_new();
    lisp_Value* value = lisp_Reader_next(reader, ')');

    while (value != NULL) {
        lisp_MutList_push(mut_list, value);
        value = lisp_Reader_next(reader, ')');
    }

    lisp_Value* list = lisp_List_from_mut_list(reader->state, mut_list);
    lisp_MutList_delete(mut_list);

    return list;
}

static lisp_Value* lisp_Reader_read_vector(lisp_Reader* reader, lisp_u32 ch) {
    lisp_MutList* mut_list = lisp_MutList_new();
    lisp_Value* value = lisp_Reader_next(reader, ']');

    while (value != NULL) {
        lisp_MutList_push(mut_list, value);
        value = lisp_Reader_next(reader, ']');
    }

    lisp_Value* vector = lisp_Vector_from_mut_list(reader->state, mut_list);
    lisp_MutList_delete(mut_list);

    return vector;
}

static lisp_Value* lisp_Reader_read_map(lisp_Reader* reader, lisp_u32 ch) {
    lisp_MutList* mut_list = lisp_MutList_new();
    lisp_Value* value = lisp_Reader_next(reader, '}');

    while (value != NULL) {
        lisp_MutList_push(mut_list, value);
        value = lisp_Reader_next(reader, '}');
    }

    lisp_Value* map = lisp_Map_from_mut_list(reader->state, mut_list);
    lisp_MutList_delete(mut_list);

    return map;
}

static lisp_Value* lisp_Reader_read_string(lisp_Reader* reader, lisp_u32 ch) {
    /* fixme - parse as utf-8 */
    lisp_Value* string_value = lisp_Value_alloc(reader->state, reader->state->type_string);
    lisp_String* string = (lisp_String*) string_value->value;

    ch = lisp_Reader_read(reader);

    while (ch != '"' && ch != '\0') {
        if (ch == '\\') {
            ch = lisp_Reader_read(reader);

            if (ch == '\0') {
                break;
            } else {
                ch = lisp_escape(ch);
            }
        }

        lisp_Value* character = lisp_Value_alloc(reader->state, reader->state->type_char);
        lisp_Char_from_ascii((lisp_Char*) character->value, ch);
        lisp_MutList_push(string->chars, character);

        ch = lisp_Reader_read(reader);
    }

    return string_value;
}

static lisp_Value* lisp_Reader_read_character(lisp_Reader* reader, lisp_u32 ch) {
    /* fixme, parse utf-8 */
    ch = lisp_Reader_read(reader);
    lisp_u32 value = ch;

    while (ch != '\'' && ch != '\0') {
        ch = lisp_Reader_read(reader);
    }

    lisp_Value* character = lisp_Value_alloc(reader->state, reader->state->type_char);
    lisp_Char_from_ascii((lisp_Char*) character->value, value);

    return character;
}

static lisp_Value* lisp_Reader_read_token(lisp_Reader* reader, lisp_u32 ch) {
    lisp_Value* value;
    lisp_u32* cstring = lisp_Reader_next_token(reader, ch);

    if (lisp_u32_char_equal(cstring, "true")) {
        value = lisp_Value_alloc(reader->state, reader->state->type_bool);
        ((lisp_Bool*) value->value)->value = LISP_TRUE;
    } else if (lisp_u32_char_equal(cstring, "false")) {
        value = lisp_Value_alloc(reader->state, reader->state->type_bool);
        ((lisp_Bool*) value->value)->value = LISP_FALSE;
    } else if (lisp_u32_char_equal(cstring, "nil")) {
        value = lisp_Value_ref(reader->state->nil);
    } else {
        value = lisp_Value_alloc(reader->state, reader->state->type_symbol);
        lisp_Symbol_from_utf8(reader->state, (lisp_Symbol*) value->value, cstring, 0);
    }
    free(cstring);

    return value;
}

static void lisp_Reader_read_comment(lisp_Reader* reader, lisp_u32 ch) {
    do {
        ch = lisp_Reader_read(reader);
    } while (ch != '\0' && ch != '\n' && ch != '\r');
}



#endif
