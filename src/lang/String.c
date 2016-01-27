#ifndef __LISP_LANG_STRING_C__
#define __LISP_LANG_STRING_C__


static void lisp_String_alloc(lisp_State* state, lisp_Value* value) {
    lisp_String* string = (lisp_String*) lisp_State_alloc(state, sizeof(lisp_String));
    value->value = string;
    string->chars = lisp_MutList_new();
    string->size = 0;
}
static void lisp_String_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_String* string = (lisp_String*) value->value;
    lisp_MutListNode* node = string->chars->root;

    while (node != NULL) {
        lisp_Value_deref(state, (lisp_Value*) node->value);
        node = node->next;
    }

    lisp_MutList_delete(string->chars);
    lisp_State_dealloc(state, string);
}

static void lisp_String_from_ascii(lisp_State* state, lisp_String* string, lisp_char* cstring, lisp_u64 start) {
    lisp_u64 i = start;
    lisp_char c = cstring[i];

    while (c != '\0') {
        lisp_Value* ch_value = lisp_Value_alloc(state, state->type_char);
        lisp_Char_from_ascii((lisp_Char*) ch_value->value, c);
        lisp_MutList_push(string->chars, ch_value);

        i += 1;
        c = cstring[i];
    }
}
static lisp_u64 lisp_String_from_utf8(lisp_State* state, lisp_String* string, lisp_u32* cstring, lisp_u64 start) {
    lisp_u64 i = start;

    while (LISP_TRUE) {
        lisp_Value* ch_value = lisp_Value_alloc(state, state->type_char);
        i = lisp_Char_from_utf8((lisp_Char*) ch_value->value, cstring, i);
        lisp_MutList_push(string->chars, ch_value);

        if (i == 0) {
            break;
        }
    }

    return i;
}

static lisp_Value* lisp_String_new_ascii(lisp_State* state, lisp_char* cstring) {
    lisp_Value* value = lisp_Value_alloc(state, state->type_string);
    lisp_String_from_ascii(state, (lisp_String*) value->value, cstring, 0);
    return value;
}
static lisp_Value* lisp_String_new_utf8(lisp_State* state, lisp_u32* cstring) {
    lisp_Value* value = lisp_Value_alloc(state, state->type_string);
    lisp_String_from_utf8(state, (lisp_String*) value->value, cstring, 0);
    return value;
}

static lisp_Value* lisp_String_concat(lisp_State* state, lisp_String* a, lisp_String* b) {
    lisp_Value* value = lisp_Value_alloc(state, state->type_string);
    lisp_String* string = (lisp_String*) value->value;

    lisp_MutListNode* node = a->chars->root;
    while (node != NULL) {
        lisp_MutList_push(string->chars, lisp_Value_ref((lisp_Value*) node->value));
        node = node->next;
    }

    node = b->chars->root;
    while (node != NULL) {
        lisp_MutList_push(string->chars, lisp_Value_ref((lisp_Value*) node->value));
        node = node->next;
    }

    string->size = a->size + b->size;

    return value;
}

static lisp_bool lisp_String_equal(lisp_String* a, lisp_String* b) {
    if (a->size != b->size) {
        return LISP_FALSE;
    } else {
        lisp_MutListNode* anode = a->chars->root;
        lisp_MutListNode* bnode = b->chars->root;

        while (anode != NULL) {
            if (lisp_Char_equal((lisp_Char*) ((lisp_Value*) anode->value)->value, (lisp_Char*) ((lisp_Value*) anode->value)->value)) {
                return LISP_FALSE;
            }
            anode = anode->next;
            bnode = bnode->next;
        }

        return LISP_TRUE;
    }
}

static lisp_char* lisp_String_to_cstring(lisp_String* string) {
    lisp_char* cstring = (lisp_char*) malloc((string->size + 1) * sizeof(lisp_char));
    lisp_MutListNode* node = string->chars->root;
    lisp_u64 index = 0;

    while (node != NULL) {
        cstring[index] = lisp_Char_to_char((lisp_Char*) ((lisp_Value*) node->value)->value);
        node = node->next;
        index += 1;
    }
    cstring[index] = '\0';

    return cstring;
}
static lisp_u32* lisp_String_to_utf8(lisp_String* string) {
    lisp_u32* cstring = (lisp_u32*) malloc((string->size + 1) * sizeof(lisp_u32));
    lisp_MutListNode* node = string->chars->root;
    lisp_u64 index = 0;

    while (node != NULL) {
        cstring[index] = lisp_Char_to_u32((lisp_Char*) ((lisp_Value*) node->value)->value);
        node = node->next;
        index += 1;
    }
    cstring[index] = '\0';

    return cstring;
}


#endif
