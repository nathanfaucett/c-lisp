#ifndef __LISP_CORE_BOOT_C__
#define __LISP_CORE_BOOT_C__


static void lisp_boot(lisp_State* state) {
    lisp_boot_Type(state, state->Type, state->nil_value, sizeof(lisp_Type), 0, false, false, NULL, NULL);

    lisp_boot_Type(state, state->Any, state->nil_value, 0, 0, true, false, NULL, NULL);
    lisp_boot_Type(state, state->Nil, state->Any, 0, 0, false, false, NULL, NULL);
    lisp_boot_Type(state, state->Annotation, state->Any, 0, 2, false, false, NULL, NULL);

    lisp_boot_Type(state, state->Collection, state->Any, 0, 0, true, false, NULL, NULL);
    lisp_boot_Type(state, state->Indexed, state->Collection, 0, 0, true, false, NULL, NULL);
    lisp_boot_Type(state, state->Keyed, state->Collection, 0, 0, true, false, NULL, NULL);

    lisp_boot_Type(state, state->List, state->Indexed, sizeof(lisp_List), 0, false, false, lisp_List_alloc, lisp_List_mark);
    lisp_boot_Type(state, state->Vector, state->Indexed, sizeof(lisp_Vector), 0, false, false, lisp_Vector_alloc, lisp_Vector_mark);

    lisp_boot_Type(state, state->Callable, state->Any, 0, 0, true, false, NULL, NULL);
    lisp_boot_Type(state, state->Native, state->Callable, 0, 0, false, false, NULL, NULL);
    lisp_boot_Type(state, state->Function, state->Callable, 0, 5, false, false, NULL, NULL);
    lisp_boot_Type(state, state->Macro, state->Callable, 0, 5, false, false, NULL, NULL);

    lisp_boot_Type(state, state->Char, state->Any, 4, 0, false, true, NULL, NULL);
    lisp_boot_Type(state, state->Symbol, state->Any, 0, 1, false, false, NULL, NULL);

    lisp_boot_Type(state, state->Number, state->Any, 0, 0, true, false, NULL, NULL);
    lisp_boot_Type(state, state->Real, state->Number, 0, 0, true, false, NULL, NULL);
    lisp_boot_Type(state, state->Float, state->Real, 0, 0, true, false, NULL, NULL);
    lisp_boot_Type(state, state->Integer, state->Real, 0, 0, true, false, NULL, NULL);
    lisp_boot_Type(state, state->Signed, state->Integer, 0, 0, true, false, NULL, NULL);
    lisp_boot_Type(state, state->Unsigned, state->Integer, 0, 0, true, false, NULL, NULL);

    lisp_boot_Type(state, state->Float32, state->Float, 4, 0, false, true, NULL, NULL);
    lisp_boot_Type(state, state->Float64, state->Float, 8, 0, false, true, NULL, NULL);

    lisp_boot_Type(state, state->UInt8, state->Unsigned, 1, 0, false, true, NULL, NULL);
    lisp_boot_Type(state, state->UInt16, state->Unsigned, 2, 0, false, true, NULL, NULL);
    lisp_boot_Type(state, state->UInt32, state->Unsigned, 4, 0, false, true, NULL, NULL);
    lisp_boot_Type(state, state->UInt64, state->Unsigned, 8, 0, false, true, NULL, NULL);

    lisp_boot_Type(state, state->Int8, state->Signed, 1, 0, false, true, NULL, NULL);
    lisp_boot_Type(state, state->Int16, state->Signed, 2, 0, false, true, NULL, NULL);
    lisp_boot_Type(state, state->Int32, state->Signed, 4, 0, false, true, NULL, NULL);
    lisp_boot_Type(state, state->Int64, state->Signed, 8, 0, false, true, NULL, NULL);

    lisp_boot_Type(state, state->Bool, state->Unsigned, 1, 0, false, true, NULL, NULL);
}

static void lisp_boot_Type (
    lisp_State* state,
    lisp_Object* value,
    lisp_Object* super,
    uintsize size,
    uintsize values_size,
    bool abstract,
    bool bytes,
    void (*alloc)(lisp_State*, lisp_Object*),
    void (*mark)(lisp_Object*)
) {
    lisp_Type* type = (lisp_Type*) value->data;

    lisp_Object* attributes = lisp_Vector_new(state, NULL);
    lisp_Vector_mut_set_size(state, (lisp_Vector*) attributes->data, values_size);
    type->attributes = attributes;

    lisp_Object* types = lisp_Vector_new(state, NULL);
    lisp_Vector_mut_set_size(state, (lisp_Vector*) types->data, values_size);
    type->types = types;

    type->size = size;
    /*
    type->prototype = lisp_Map_new(state);
    type->template = lisp_Map_new(state);
    */
    type->abstract = abstract;
    type->bytes = bytes;

    type->alloc = alloc;
    type->mark = mark;
}


#endif
