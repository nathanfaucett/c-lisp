#ifndef __LISP_LANG_VALUE_C__
#define __LISP_LANG_VALUE_C__


inline static lisp_Value* lisp_Value_constructor(lisp_Value* value, LISP_TYPE type) {
    value->type = type;
    value->ref_count = 1;
    return value;
}

inline static void lisp_Value_destructor(lisp_State* state, lisp_Value* value) {
    switch (value->type) {
        case LISP_TYPE_CHARACTER:
            lisp_Character_destructor(&value->character);
            break;
        case LISP_TYPE_LIST:
            lisp_List_destructor(state, &value->list);
            break;
        case LISP_TYPE_STRING:
            lisp_String_destructor(state, &value->string);
            break;
        case LISP_TYPE_SYMBOL:
            lisp_Symbol_destructor(state, &value->symbol);
            break;
        case LISP_TYPE_NIL:
        case LISP_TYPE_NUMBER:
            break;
    }
}

inline static lisp_Value* lisp_Value_new(lisp_State* state, LISP_TYPE type) {
    return lisp_Value_constructor(lisp_State_alloc(state), type);
}

inline static void lisp_Value_delete(lisp_State* state, lisp_Value* value) {
    lisp_Value_destructor(state, value);
    lisp_State_dealloc(state, value);
}

inline static lisp_Value* lisp_Value_character_from_ch(lisp_State* state, lisp_u8 ch) {
    lisp_Value* value = lisp_Value_new(state, LISP_TYPE_CHARACTER);
    value->character.value = value;
    lisp_Character_from_u8(&value->character, ch);
    return value;
}

inline static lisp_Value* lisp_Value_string_from_cstring(lisp_State* state, lisp_u8* cstring) {
    lisp_Value* value = lisp_Value_new(state, LISP_TYPE_STRING);
    value->string.value = value;
    lisp_String_from_cstring(state, &value->string, cstring);
    return value;
}

inline static lisp_Value* lisp_Value_symbol_from_cstring(lisp_State* state, lisp_u8* cstring) {
    lisp_Value* value = lisp_Value_new(state, LISP_TYPE_SYMBOL);
    value->symbol.value = value;
    lisp_Symbol_from_cstring(state, &value->symbol, cstring);
    return value;
}

inline static lisp_Value* lisp_Value_number_from_i32(lisp_State* state, lisp_i32 i32) {
    lisp_Value* value = lisp_Value_new(state, LISP_TYPE_NUMBER);
    value->number.value = value;
    lisp_Number_from_i32(&value->number, i32);
    return value;
}

inline static lisp_Value* lisp_Value_number_from_f64(lisp_State* state, lisp_f64 f64) {
    lisp_Value* value = lisp_Value_new(state, LISP_TYPE_NUMBER);
    value->number.value = value;
    lisp_Number_from_f64(&value->number, f64);
    return value;
}

inline static lisp_Value* lisp_Value_nil(lisp_State* state) {
    lisp_Value* nil = state->nil;
    lisp_Value_ref(nil);
    return nil;
}

inline static lisp_Value* lisp_Value_list(lisp_State* state) {
    lisp_Value* empty_list = state->empty_list;
    lisp_Value_ref(empty_list);
    return empty_list;
}

inline static lisp_Value* lisp_Value_new_nil(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, LISP_TYPE_NIL);
    value->nil.value = value;
    return value;
}

inline static lisp_Value* lisp_Value_new_list(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, LISP_TYPE_LIST);
    value->list.value = value;
    lisp_List_constructor(&value->list, NULL, NULL, 0);
    return value;
}

inline static void lisp_Value_ref(lisp_Value* value) {
    value->ref_count += 1;
}

inline static void lisp_Value_deref(lisp_State* state, lisp_Value* value) {
    value->ref_count -= 1;

    if (value->ref_count == 0) {
        lisp_Value_delete(state, value);
    }
}

inline static lisp_Value* lisp_Value_to_string(lisp_State* state, lisp_Value* value) {
    switch (value->type) {
        case LISP_TYPE_CHARACTER:
            return lisp_Character_to_string(state, &value->character);
        case LISP_TYPE_LIST:
            return lisp_List_to_string(state, &value->list);
        case LISP_TYPE_NIL:
            return lisp_Nil_to_string(state);
        case LISP_TYPE_NUMBER:
            return lisp_Number_to_string(state, &value->number);
        case LISP_TYPE_STRING:
            lisp_Value_ref(value);
            return value;
        case LISP_TYPE_SYMBOL:
            return lisp_Symbol_to_string(state, &value->symbol);
    }
}


#endif
