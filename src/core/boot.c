#ifndef __LISP_BOOT_C__
#define __LISP_BOOT_C__


static void lisp_boot(lisp_State* state) {

    lisp_boot_MainType(state, state->Type);

    lisp_boot_Type(state, state->Any, state->nil, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);

    lisp_boot_Type(state, state->Nil, state->Any, 0, 0, LISP_FALSE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Annotation, state->Any, 0, 2, LISP_FALSE, LISP_FALSE, NULL, NULL);

    lisp_boot_Type(state, state->Collection, state->Any, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Indexed, state->Collection, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Keyed, state->Collection, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);

    lisp_boot_Type(state, state->MutableList, state->Indexed, sizeof(lisp_MutableList), 0, LISP_FALSE, LISP_FALSE, lisp_MutableList_alloc, lisp_MutableList_mark);
    lisp_boot_Type(state, state->MutableMap, state->Keyed, sizeof(lisp_MutableMap), 0, LISP_FALSE, LISP_FALSE, lisp_MutableMap_alloc, lisp_MutableMap_mark);

    lisp_boot_Type(state, state->Callable, state->Any, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Native, state->Callable, 0, 0, LISP_FALSE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Function, state->Callable, 0, 2, LISP_FALSE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Macro, state->Callable, 0, 2, LISP_FALSE, LISP_FALSE, NULL, NULL);

    lisp_boot_Type(state, state->Char, state->Any, 4, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);
    lisp_boot_Type(state, state->String, state->Indexed, sizeof(lisp_String), 0, LISP_FALSE, LISP_FALSE, lisp_String_alloc, lisp_String_mark);
    lisp_boot_Type(state, state->Symbol, state->Any, sizeof(lisp_Symbol), 0, LISP_FALSE, LISP_FALSE, lisp_Symbol_alloc, lisp_Symbol_mark);

    lisp_boot_Type(state, state->Number, state->Any, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Real, state->Number, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Float, state->Real, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Integer, state->Real, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Signed, state->Integer, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Unsigned, state->Integer, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);

    lisp_boot_Type(state, state->Float32, state->Float, 4, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);
    lisp_boot_Type(state, state->Float64, state->Float, 8, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);

    lisp_boot_Type(state, state->UInt8, state->Unsigned, 1, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);
    lisp_boot_Type(state, state->UInt16, state->Unsigned, 2, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);
    lisp_boot_Type(state, state->UInt32, state->Unsigned, 4, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);
    lisp_boot_Type(state, state->UInt64, state->Unsigned, 8, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);

    lisp_boot_Type(state, state->Int8, state->Signed, 1, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);
    lisp_boot_Type(state, state->Int16, state->Signed, 2, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);
    lisp_boot_Type(state, state->Int32, state->Signed, 4, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);
    lisp_boot_Type(state, state->Int64, state->Signed, 8, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);

    lisp_boot_Type(state, state->Bool, state->Unsigned, 1, 0, LISP_FALSE, LISP_TRUE, NULL, NULL);

    lisp_Native_boot(state);
}

static void lisp_boot_MainType(lisp_State* state, lisp_Object* type) {
    lisp_Type* type_data = (lisp_Type*) type->data;

    type_data->alloc = NULL;
    type_data->mark = NULL;

    lisp_MutableList* values = lisp_State_assoc(state, type->gc_node, sizeof(lisp_MutableList));
    lisp_MutableList_init(values, type->gc_node);
    lisp_MutableList_set_size(state, values, LISP_TYPE_SIZE);

    lisp_Object* size_object = lisp_boot_assoc_size(state, type->gc_node, state->UInt, sizeof(lisp_size));
    LISP_SET_DATA(size_object, lisp_size, sizeof(lisp_Type));
    lisp_MutableList_set(values, LISP_IDX_TYPE_SIZE, size_object);

    type->type = type;
    type->values = values;
}
static void lisp_boot_Type (
    lisp_State* state,
    lisp_Object* type,
    lisp_Object* super,
    lisp_size size,
    lisp_size values_size,
    lisp_bool abstract,
    lisp_bool bytes,
    void (*alloc)(lisp_State*, lisp_Object*),
    void (*mark)(lisp_Object*)
) {
    lisp_MutableList* values = lisp_State_assoc(state, type->gc_node, sizeof(lisp_MutableList));
    lisp_MutableList_init(values, type->gc_node);
    lisp_MutableList_set_size(state, values, LISP_TYPE_SIZE);

    lisp_Object* size_object = lisp_boot_new_size(state, state->UInt, sizeof(lisp_size), LISP_FALSE);
    LISP_SET_DATA(size_object, lisp_size, size);

    lisp_Object* attributes = lisp_boot_new_mutable_list(state, LISP_FALSE);
    lisp_MutableList_set_size(state, (lisp_MutableList*) attributes->data, values_size);
    lisp_MutableList_set(values, LISP_IDX_TYPE_ATTRIBUTES, attributes);

    lisp_Object* types = lisp_boot_new_mutable_list(state, LISP_FALSE);
    lisp_MutableList_set_size(state, (lisp_MutableList*) types->data, values_size);
    lisp_MutableList_set(values, LISP_IDX_TYPE_TYPES, types);

    lisp_MutableList_set(values, LISP_IDX_TYPE_SIZE, size_object);
    lisp_MutableList_set(values, LISP_IDX_TYPE_SUPER, super);

    lisp_MutableList_set(values, LISP_IDX_TYPE_PROTOTYPE, lisp_boot_new_mutable_map(state, LISP_FALSE));
    lisp_MutableList_set(values, LISP_IDX_TYPE_TEMPLATE, lisp_boot_new_mutable_map(state, LISP_FALSE));

    lisp_MutableList_set(values, LISP_IDX_TYPE_ABSTRACT, lisp_boot_new_bool(state, abstract));
    lisp_MutableList_set(values, LISP_IDX_TYPE_BYTES, lisp_boot_new_bool(state, bytes));

    lisp_Type* type_data = lisp_State_assoc(state, type->gc_node, sizeof(lisp_Type));
    type_data->alloc = alloc;
    type_data->mark = mark;

    type->data = type_data;
    type->values = values;
}

static lisp_Object* lisp_boot_alloc_object(lisp_State* state, lisp_Object* type, lisp_bool is_static) {
    lisp_GCNode* gc_node;
    if (is_static) {
        gc_node = lisp_State_static_alloc(state, sizeof(lisp_Object));
    } else {
        gc_node = lisp_State_alloc(state, sizeof(lisp_Object));
    }
    lisp_Object* object = (lisp_Object*) gc_node->object;
    lisp_boot_init_object(object, gc_node, type);
    return object;
}
static lisp_Object* lisp_boot_init_object(lisp_Object* object, lisp_GCNode* gc_node, lisp_Object* type) {
    object->gc_node = gc_node;
    object->data = NULL;
    object->type = type;
    object->values = NULL;
    return object;
}
static lisp_Object* lisp_boot_new_size(lisp_State* state, lisp_Object* type, lisp_size size, lisp_bool is_static) {
    lisp_Object* object = lisp_boot_alloc_object(state, type, is_static);
    if (size != 0) {
        object->data = lisp_State_assoc(state, object->gc_node, size);
    }
    return object;
}
static lisp_Object* lisp_boot_new_mutable_list(lisp_State* state, lisp_bool is_static) {
    lisp_Object* object = lisp_boot_new_size(state, state->MutableList, sizeof(lisp_MutableList), is_static);
    lisp_MutableList_init((lisp_MutableList*) object->data, object->gc_node);
    return object;
}
static lisp_Object* lisp_boot_new_mutable_map(lisp_State* state, lisp_bool is_static) {
    lisp_Object* object = lisp_boot_new_size(state, state->MutableMap, sizeof(lisp_MutableList), is_static);
    lisp_MutableMap_init(state, (lisp_MutableMap*) object->data, object->gc_node);
    return object;
}
static lisp_Object* lisp_boot_new_bool(lisp_State* state, lisp_bool value) {
    lisp_Object* object = lisp_boot_new_size(state, state->Bool, 1, LISP_FALSE);
    LISP_SET_DATA(object, lisp_bool, value);
    return object;
}
static lisp_Object* lisp_boot_assoc_size(lisp_State* state, lisp_GCNode* gc_node, lisp_Object* type, lisp_size size) {
    lisp_Object* object = lisp_State_assoc(state, gc_node, sizeof(lisp_Object));
    if (size != 0) {
        object->data = lisp_State_assoc(state, gc_node, size);
    }
    return object;
}


#endif
