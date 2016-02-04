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

    lisp_boot_Type(state, state->MutableList, state->Indexed, sizeof(lisp_MutableList), 0, LISP_FALSE, LISP_FALSE, lisp_MutableList_alloc, lisp_MutableList_dealloc, lisp_MutableList_mark);
    lisp_boot_Type(state, state->MutableMap, state->Keyed, sizeof(lisp_MutableMap), 0, LISP_FALSE, LISP_FALSE, lisp_MutableMap_alloc, lisp_MutableMap_dealloc, lisp_MutableMap_mark);

    lisp_boot_Type(state, state->List, state->Indexed, sizeof(lisp_List), 0, LISP_FALSE, LISP_FALSE, lisp_List_alloc, NULL, lisp_List_mark);
    lisp_boot_Type(state, state->ListNode, state->Any, sizeof(lisp_ListNode), 0, LISP_FALSE, LISP_FALSE, lisp_ListNode_alloc, NULL, lisp_ListNode_mark);
    lisp_boot_Type(state, state->Map, state->Keyed, sizeof(lisp_Map), 0, LISP_FALSE, LISP_FALSE, lisp_Map_alloc, NULL, lisp_Map_mark);

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
    lisp_Native_boot(state);
}

static void lisp_boot_MainType(lisp_State* state) {
    lisp_Value* Type = state->Type;
    lisp_Type* data = (lisp_Type*) Type->data;

    data->alloc = NULL;
    data->dealloc = NULL;
    data->mark = NULL;

    lisp_Value* values = lisp_boot_new_list(state);
    lisp_MutableList* values_list = (lisp_MutableList*) values->data;
    lisp_MutableList_set_size(state, values_list, LISP_TYPE_SIZE);

    lisp_Value* size_value = lisp_boot_new_size(state, state->UInt, sizeof(lisp_size));
    LISP_SET_DATA(size_value, lisp_size, sizeof(lisp_Type));
    lisp_MutableList_set(values_list, LISP_IDX_TYPE_SIZE, size_value);

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
    lisp_Value* values = lisp_boot_new_mutablelist(state);
    lisp_MutableList* values_list = (lisp_MutableList*) values->data;
    lisp_MutableList_set_size(state, values_list, LISP_TYPE_SIZE);

    lisp_Value* size_value = lisp_boot_new_size(state, state->UInt, sizeof(lisp_size));
    LISP_SET_DATA(size_value, lisp_size, size);

    lisp_Value* attributes = lisp_boot_new_mutablelist(state);
    lisp_MutableList_set_size(state, (lisp_MutableList*) attributes->data, values_size);
    lisp_MutableList_set(values_list, LISP_IDX_TYPE_ATTRIBUTES, attributes);

    lisp_Value* types = lisp_boot_new_mutablelist(state);
    lisp_MutableList_set_size(state, (lisp_MutableList*) types->data, values_size);
    lisp_MutableList_set(values_list, LISP_IDX_TYPE_TYPES, types);

    lisp_MutableList_set(values_list, LISP_IDX_TYPE_PROTOTYPE, lisp_boot_new_mutablemap(state));
    lisp_MutableList_set(values_list, LISP_IDX_TYPE_TEMPLATE, lisp_boot_new_mutablemap(state));

    lisp_MutableList_set(values_list, LISP_IDX_TYPE_SIZE, size_value);
    lisp_MutableList_set(values_list, LISP_IDX_TYPE_SUPER, super);

    if (abstract == LISP_TRUE) {
        lisp_MutableList_set(values_list, LISP_IDX_TYPE_ABSTRACT, state->true);
    } else {
        lisp_MutableList_set(values_list, LISP_IDX_TYPE_ABSTRACT, state->false);
    }
    if (bytes == LISP_TRUE) {
        lisp_MutableList_set(values_list, LISP_IDX_TYPE_BYTES, state->true);
    } else {
        lisp_MutableList_set(values_list, LISP_IDX_TYPE_BYTES, state->false);
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


static lisp_Value* lisp_boot_new_mutablelist(lisp_State* state) {
    lisp_Value* value = lisp_boot_new_size(state, state->List, sizeof(lisp_MutableList));
    lisp_MutableList_alloc(state, value);
    return value;
}
static lisp_Value* lisp_boot_new_mutablemap(lisp_State* state) {
    lisp_Value* value = lisp_boot_new_size(state, state->List, sizeof(lisp_MutableMap));
    lisp_MutableMap_alloc(state, value);
    return value;
}

static lisp_Value* lisp_boot_new_list(lisp_State* state) {
    lisp_Value* value = lisp_boot_new_size(state, state->List, sizeof(lisp_List));
    lisp_List_alloc(state, value);
    return value;
}
static lisp_Value* lisp_boot_new_list_node(lisp_State* state) {
    lisp_Value* value = lisp_boot_new_size(state, state->ListNode, sizeof(lisp_ListNode));
    lisp_ListNode_alloc(state, value);
    return value;
}
static lisp_Value* lisp_boot_new_map(lisp_State* state) {
    lisp_Value* value = lisp_boot_new_size(state, state->Map, sizeof(lisp_Map));
    lisp_Map_alloc(state, value);
    return value;
}

#endif
