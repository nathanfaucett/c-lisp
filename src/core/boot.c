#ifndef __LISP_BOOT_C__
#define __LISP_BOOT_C__


static void lisp_boot(lisp_State* state) {
    lisp_boot_Type(state, state->Type, state->nil, sizeof(lisp_Type), LISP_TYPE_SIZE, LISP_FALSE, LISP_FALSE, NULL, NULL);

    lisp_boot_Type(state, state->Any, state->nil, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);

    lisp_boot_Type(state, state->Nil, state->Any, 0, 0, LISP_FALSE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Scope, state->Any, sizeof(lisp_Scope), 0, LISP_FALSE, LISP_FALSE, lisp_Scope_alloc, lisp_Scope_mark);
    lisp_boot_Type(state, state->Annotation, state->Any, 0, 2, LISP_FALSE, LISP_FALSE, NULL, NULL);

    lisp_boot_Type(state, state->Collection, state->Any, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Indexed, state->Collection, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Keyed, state->Collection, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);

    lisp_boot_Type(state, state->List, state->Indexed, sizeof(lisp_List), 0, LISP_FALSE, LISP_FALSE, lisp_List_alloc, lisp_List_mark);
    lisp_boot_Type(state, state->ListNode, state->Any, sizeof(lisp_ListNode), 0, LISP_FALSE, LISP_FALSE, lisp_ListNode_alloc, lisp_ListNode_mark);
    lisp_boot_Type(state, state->Vector, state->Indexed, sizeof(lisp_Vector), 0, LISP_FALSE, LISP_FALSE, lisp_Vector_alloc, lisp_Vector_mark);
    lisp_boot_Type(state, state->VectorNode, state->Any, sizeof(lisp_VectorNode), 0, LISP_FALSE, LISP_FALSE, lisp_VectorNode_alloc, lisp_VectorNode_mark);
    lisp_boot_Type(state, state->Map, state->Keyed, sizeof(lisp_Map), 0, LISP_FALSE, LISP_FALSE, lisp_Map_alloc, lisp_Map_mark);

    lisp_boot_Type(state, state->Callable, state->Any, 0, 0, LISP_TRUE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Native, state->Callable, 0, 0, LISP_FALSE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Function, state->Callable, 0, 5, LISP_FALSE, LISP_FALSE, NULL, NULL);
    lisp_boot_Type(state, state->Macro, state->Callable, 0, 5, LISP_FALSE, LISP_FALSE, NULL, NULL);

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

    lisp_Type_boot(state);

    lisp_Nil_boot(state);

    lisp_String_boot(state);
    lisp_Symbol_boot(state);

    lisp_List_boot(state);
    lisp_Map_boot(state);

    lisp_Bool_boot(state);

    state->scope = lisp_Scope_new(state, NULL);
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
    lisp_Object* values_object = lisp_List_new(state);
    lisp_List* values = (lisp_List*) values_object->data;
    lisp_List_mut_set_size(state, values, LISP_TYPE_SIZE);

    lisp_Object* size_object = lisp_Object_boot_size(state, state->UInt, sizeof(lisp_size));
    LISP_SET_DATA(size_object, lisp_size, size);

    lisp_Object* attributes = lisp_List_new(state);
    lisp_List_mut_set_size(state, (lisp_List*) attributes->data, values_size);
    lisp_List_mut_set(values, LISP_IDX_TYPE_ATTRIBUTES, attributes);

    lisp_Object* types = lisp_List_new(state);
    lisp_List_mut_set_size(state, (lisp_List*) types->data, values_size);
    lisp_List_mut_set(values, LISP_IDX_TYPE_TYPES, types);

    lisp_List_mut_set(values, LISP_IDX_TYPE_SIZE, size_object);
    lisp_List_mut_set(values, LISP_IDX_TYPE_SUPER, super);

    lisp_List_mut_set(values, LISP_IDX_TYPE_PROTOTYPE, lisp_Map_new(state));
    lisp_List_mut_set(values, LISP_IDX_TYPE_TEMPLATE, lisp_Map_new(state));

    lisp_List_mut_set(values, LISP_IDX_TYPE_ABSTRACT, (abstract == LISP_TRUE) ? state->true : state->false);
    lisp_List_mut_set(values, LISP_IDX_TYPE_BYTES, (bytes == LISP_TRUE) ? state->true : state->false);

    lisp_Type* type_data = lisp_State_assoc(state, type->gc_node, sizeof(lisp_Type));
    type_data->alloc = alloc;
    type_data->mark = mark;

    type->values = values_object;
    type->data = type_data;
}


#endif
