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
        lisp_Value* ch_value = lisp_Value_new(state, state->type_char);
        lisp_Char_from_ascii((lisp_Char*) ch_value->value, c);
        lisp_MutList_push(string->chars, ch_value);

        i += 1;
        c = cstring[i];
    }
}
static lisp_u64 lisp_String_from_utf8(lisp_State* state, lisp_String* string, lisp_u64* cstring, lisp_u64 start) {
    lisp_u64 i = start;

    while (LISP_TRUE) {
        lisp_Value* ch_value = lisp_Value_new(state, state->type_char);
        i = lisp_Char_from_utf8((lisp_Char*) ch_value->value, cstring, i);
        lisp_MutList_push(string->chars, ch_value);

        if (i == 0) {
            break;
        }
    }

    return i;
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


#endif
