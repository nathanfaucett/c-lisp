#ifndef __LISP_BOOT_C__
#define __LISP_BOOT_C__


static void lisp_boot(lisp_State* state) {
    lisp_boot_MainType(state);

    lisp_boot_Type(state, state->Any, state->nil, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);

    lisp_boot_Type(state, state->Nil, state->Any, 0, 0, LISP_FALSE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Annotation, state->Any, 0, 2, LISP_FALSE, LISP_FALSE, NULL, NULL, NULL);

    lisp_boot_Type(state, state->Collection, state->Any, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Indexed, state->Collection, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Keyed, state->Collection, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);

    lisp_boot_Type(state, state->Array, state->Indexed, sizeof(lisp_Array), 0, LISP_FALSE, LISP_FALSE, lisp_Array_alloc, lisp_Array_dealloc, lisp_Array_mark);
    lisp_boot_Type(state, state->Map, state->Keyed, sizeof(lisp_Map), 0, LISP_FALSE, LISP_FALSE, NULL, NULL, NULL);

    lisp_boot_Type(state, state->Callable, state->Any, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Native, state->Callable, 0, 0, LISP_FALSE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Function, state->Callable, 0, 2, LISP_FALSE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Macro, state->Callable, 0, 2, LISP_FALSE, LISP_FALSE, NULL, NULL, NULL);

    lisp_boot_Type(state, state->Char, state->Any, 4, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->String, state->Indexed, sizeof(lisp_String), 0, LISP_FALSE, LISP_FALSE, lisp_String_alloc, lisp_String_dealloc, lisp_String_mark);
    lisp_boot_Type(state, state->Symbol, state->Any, 0, 1, LISP_FALSE, LISP_FALSE, NULL, NULL, NULL);

    lisp_boot_Type(state, state->Number, state->Any, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Real, state->Number, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Float, state->Real, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Integer, state->Real, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Signed, state->Integer, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Unsigned, state->Integer, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL, NULL);

    lisp_boot_Type(state, state->Float32, state->Float, 4, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Float64, state->Float, 8, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);

    lisp_boot_Type(state, state->UInt8, state->Unsigned, 1, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->UInt16, state->Unsigned, 2, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->UInt32, state->Unsigned, 4, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->UInt64, state->Unsigned, 8, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);

    lisp_boot_Type(state, state->Int8, state->Signed, 1, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Int16, state->Signed, 2, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Int32, state->Signed, 4, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);
    lisp_boot_Type(state, state->Int64, state->Signed, 8, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);

    lisp_boot_Type(state, state->Bool, state->Signed, 1, 0, LISP_FALSE, LISP_TRUE, NULL, NULL, NULL);

    lisp_Annotation_boot(state);
    lisp_Symbol_boot(state);
}

static void lisp_boot_MainType(lisp_State* state) {
    lisp_Value* Type = state->Type;
    lisp_Type* data = (lisp_Type*) Type->data;

    data->alloc = NULL;
    data->dealloc = NULL;
    data->mark = NULL;

    lisp_Value* values = lisp_boot_new_array(state);
    lisp_Array* values_array = (lisp_Array*) values->data;
    lisp_Array_set_size(state, values_array, LISP_TYPE_SIZE);

    lisp_Value* size_value = lisp_boot_new_size(state, state->UInt, sizeof(lisp_size));
    LISP_SET_DATA(size_value, lisp_size, sizeof(lisp_Type));
    lisp_Array_set(values_array, LISP_IDX_TYPE_SIZE, size_value);

    Type->type = Type;
    Type->values = values;
}

static void lisp_boot_Type (
    lisp_State* state,
    lisp_Value* value,
    lisp_Value* super,
    lisp_size size,
    lisp_size values_size,
    lisp_bool abstract,
    lisp_bool bytes,
    void (*alloc)(lisp_State*, lisp_Value*),
    void (*dealloc)(lisp_State*, lisp_Value*),
    void (*mark)(lisp_Value*)
) {
    lisp_Value* values = lisp_boot_new_array(state);
    lisp_Array* values_array = (lisp_Array*) values->data;
    lisp_Array_set_size(state, values_array, LISP_TYPE_SIZE);

    lisp_Value* size_value = lisp_boot_new_size(state, state->UInt, sizeof(lisp_size));
    LISP_SET_DATA(size_value, lisp_size, size);

    lisp_Value* attributes = lisp_boot_new_array(state);
    lisp_Array_set_size(state, (lisp_Array*) attributes->data, values_size);
    lisp_Array_set(values_array, LISP_IDX_TYPE_ATTRIBUTES, attributes);

    lisp_Value* types = lisp_boot_new_array(state);
    lisp_Array_set_size(state, (lisp_Array*) types->data, values_size);
    lisp_Array_set(values_array, LISP_IDX_TYPE_TYPES, types);

    lisp_Array_set(values_array, LISP_IDX_TYPE_PROTOTYPE, lisp_boot_new_map(state));
    lisp_Array_set(values_array, LISP_IDX_TYPE_TEMPLATE, lisp_boot_new_map(state));

    lisp_Array_set(values_array, LISP_IDX_TYPE_SIZE, size_value);
    lisp_Array_set(values_array, LISP_IDX_TYPE_SUPER, super);

    if (abstract == LISP_TRUE) {
        lisp_Array_set(values_array, LISP_IDX_TYPE_ABSTRACT, state->true);
    } else {
        lisp_Array_set(values_array, LISP_IDX_TYPE_ABSTRACT, state->false);
    }
    if (bytes == LISP_TRUE) {
        lisp_Array_set(values_array, LISP_IDX_TYPE_BYTES, state->true);
    } else {
        lisp_Array_set(values_array, LISP_IDX_TYPE_BYTES, state->false);
    }

    lisp_Type* type = lisp_State_alloc(state, sizeof(lisp_Type));
    type->alloc = alloc;
    type->dealloc = dealloc;
    type->mark = mark;

    value->data = type;
    value->values = values;
}

static lisp_Value* lisp_boot_new_value(lisp_State* state, lisp_Value* type) {
    lisp_Value* value = lisp_State_alloc(state, sizeof(lisp_Value));
    value->marked = LISP_FALSE;
    value->data = NULL;
    value->type = type;
    value->values = NULL;
    value->template = NULL;
    return value;
}
static lisp_Value* lisp_boot_new_size(lisp_State* state, lisp_Value* type, lisp_size size) {
    lisp_Value* value = lisp_boot_new_value(state, type);
    if (size != 0) {
        value->data = lisp_State_alloc(state, size);
    }
    return value;
}
static lisp_Value* lisp_boot_new_array(lisp_State* state) {
    lisp_Value* value = lisp_boot_new_size(state, state->Array, sizeof(lisp_Array));
    lisp_Array_alloc(state, value);
    return value;
}
static lisp_Value* lisp_boot_new_map(lisp_State* state) {
    lisp_Value* value = lisp_boot_new_size(state, state->Map, sizeof(lisp_Map));
    lisp_Map_alloc(state, value);
    return value;
}

#endif
