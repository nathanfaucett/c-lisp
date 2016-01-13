#ifndef __LISP_LANG_VALUE_C__
#define __LISP_LANG_VALUE_C__


inline static lisp_Value* lisp_Value_ch(lisp_State* state, lisp_u8 ch) {
    lisp_Value* value = lisp_State_alloc(state);
    value->type = LISP_TYPE_CHARACTER;
    value->character.value = value;
    value->ref_count = 1;
    lisp_Character_u8(&value->character, ch);
    return value;
}

inline static lisp_Value* lisp_Value_cstring(lisp_State* state, lisp_u8* cstring) {
    lisp_Value* value = lisp_State_alloc(state);
    value->type = LISP_TYPE_STRING;
    value->string.value = value;
    value->ref_count = 1;
    lisp_String_cstring(state, &value->string, cstring);
    return value;
}

inline static lisp_Value* lisp_Value_nil(lisp_State* state) {
    lisp_Value* value = lisp_State_alloc(state);
    value->type = LISP_TYPE_NIL;
    value->nil.value = value;
    value->ref_count = 1;
    return value;
}

inline static lisp_Value* lisp_Value_number(lisp_State* state, lisp_f64 float_value) {
    lisp_Value* value = lisp_State_alloc(state);
    value->type = LISP_TYPE_NUMBER;
    value->number.value = value;
    value->ref_count = 1;
    lisp_Number_new(&value->number, float_value);
    return value;
}

inline static lisp_Value* lisp_Value_list(lisp_State* state) {
    lisp_Value* value = lisp_State_alloc(state);
    value->type = LISP_TYPE_LIST;
    value->list.value = value;
    value->ref_count = 1;
    lisp_List_new(&value->list, NULL, NULL, 0);
    return value;
}

inline static void lisp_Value_delete(lisp_State* state, lisp_Value* value) {
    switch (value->type) {
        case LISP_TYPE_CHARACTER:
            lisp_Character_delete(&value->character);
            break;
        case LISP_TYPE_LIST:
            lisp_List_delete(state, &value->list);
            break;
        case LISP_TYPE_STRING:
            lisp_String_delete(state, &value->string);
            break;
        case LISP_TYPE_NIL:
        case LISP_TYPE_NUMBER:
            break;
    }
    lisp_State_dealloc(state, value);
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
            return value;
    }
}


#endif
