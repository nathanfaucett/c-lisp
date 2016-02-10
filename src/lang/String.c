#ifndef __LISP_LANG_STRING_C__
#define __LISP_LANG_STRING_C__


static void lisp_String_alloc(lisp_State* state, lisp_Object* object) {
    lisp_String* string = (lisp_String*) object->data;
    string->chars = NULL;
    string->size = 0;
}
static void lisp_String_mark(lisp_Object* object) {
    lisp_String* string = (lisp_String*) object->data;

    if (string->chars != NULL) {
        lisp_usize i = 0, il = string->size;
        for (; i < il; i++) {
            lisp_Object_mark(string->chars[i]);
        }
    }
}

static lisp_Object* lisp_String_from_ascii(lisp_State* state, lisp_char* ascii) {
    lisp_Object* object = lisp_Object_alloc(state, state->String);
    lisp_String* string = (lisp_String*) object->data;

    lisp_usize size = lisp_ascii_size(ascii);
    lisp_Object** chars = (lisp_Object**) lisp_State_assoc(state, object->gc_node, size * sizeof(lisp_Object*));

    lisp_usize i = 0, il = size;
    for (; i < il; i++) {
        lisp_Object* object = lisp_Object_alloc(state, state->Char);
        LISP_SET_DATA(object, lisp_u32, ascii[i]);
        chars[i] = object;
    }

    string->chars = chars;
    string->size = size;

    return object;
}
static lisp_char* lisp_String_to_ascii(lisp_String* string) {
    lisp_char* ascii = (lisp_char*) malloc((string->size + 1) * sizeof(lisp_char));

    lisp_usize i = 0, il = string->size;
    for (; i < il; i++) {
        ascii[i] = (lisp_char) *((lisp_u32*) string->chars[i]->data);
    }
    ascii[string->size] = '\0';

    return ascii;
}

static lisp_Object* lisp_String_concat(lisp_State* state, lisp_String* a, lisp_String* b) {
    lisp_Object* object = lisp_Object_alloc(state, state->String);
    lisp_String* string = (lisp_String*) object->data;

    lisp_usize size = a->size + b->size;
    lisp_Object** chars = (lisp_Object**) lisp_State_assoc(state, object->gc_node, size * sizeof(lisp_Object*));

    lisp_usize i = 0, il = a->size, k = 0;
    for (; i < il; i++) {
        chars[i] = a->chars[i];
    }
    i = a->size, il = size;
    for (; i < il; i++, k++) {
        chars[i] = b->chars[k];
    }

    string->chars = chars;
    string->size = size;

    return object;
}

static lisp_bool lisp_String_equal(lisp_String* a, lisp_String* b) {
    if (a == b) {
        return LISP_TRUE;
    } else if (a->size == b->size) {
        lisp_usize i = 0, il = a->size;
        for (; i < il; i++) {
            if (LISP_GET_DATA(a->chars[i], lisp_u32) != LISP_GET_DATA(b->chars[i], lisp_u32)) {
                return LISP_FALSE;
            }
        }
        return LISP_TRUE;
    } else {
        return LISP_FALSE;
    }
}

static lisp_Object* lisp_String_export_char_at(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_List* list = (lisp_List*) args->data;
    lisp_Object* self = lisp_List_get(state, list, 0);
    lisp_Object* index = lisp_List_get(state, list, 1);

    if (self->type == state->String && lisp_Object_inherits(state, index->type, state->Unsigned)) {
        lisp_String* string = (lisp_String*) self->data;
        lisp_usize i = lisp_Number_get_UInt(state, index);

        if (string->chars != NULL && i < string->size) {
            return string->chars[lisp_Number_get_UInt(state, index)];
        } else {
            return state->empty_char;
        }
    } else {
        return state->empty_char;
    }
}
static lisp_Object* lisp_String_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Object* self = lisp_List_get(state, (lisp_List*) args->data, 0);

    if (self->type == state->String) {
        return self;
    } else {
        return lisp_Object_to_string(state, self);
    }
}
static lisp_Object* lisp_String_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_List* list = (lisp_List*) args->data;
    lisp_Object* self = lisp_List_get(state, list, 0);
    lisp_Object* other = lisp_List_get(state, list, 1);

    if (self->type == state->String && other->type == state->String) {
        return lisp_String_equal((lisp_String*) self->data, (lisp_String*) other->data) ? state->true : state->false;
    } else {
        return lisp_Object_equal(state, self, other) ? state->true : state->false;
    }
}

static void lisp_String_boot(lisp_State* state) {
    lisp_Object* String = state->String;
    lisp_List* values = (lisp_List*) String->values->data;
    lisp_Map* prototype = (lisp_Map*) lisp_List_get(state, values, LISP_IDX_TYPE_PROTOTYPE)->data;

    lisp_List_mut_set(values, LISP_IDX_TYPE_NAME, lisp_String_from_ascii(state, "String"));

    lisp_Map_mut_set(state, prototype, lisp_String_from_ascii(state, "char-at"), lisp_Native_new(state, lisp_String_export_char_at));
    lisp_Map_mut_set(state, prototype, lisp_String_from_ascii(state, "to-string"), lisp_Native_new(state, lisp_String_export_to_string));
    lisp_Map_mut_set(state, prototype, lisp_String_from_ascii(state, "equal"), lisp_Native_new(state, lisp_String_export_equal));
}


#endif
