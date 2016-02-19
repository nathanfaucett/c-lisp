#ifndef __LISP_BOOT_C__
#define __LISP_BOOT_C__


static void lisp_boot(lisp_State* state) {
    uintsize ptr_size = sizeof(void*);

    lisp_boot_type(state, state->Type, state->nil, LISP_TYPE_SIZE * ptr_size, false, false, false, true);

    lisp_boot_type(state, state->Any, state->nil, 0, false, true, false, true);
    lisp_boot_type(state, state->Nil, state->Any, 0, false, false, false, true);
    lisp_boot_type(state, state->Annotation, state->Any, 2 * ptr_size, false, false, false, true);

    lisp_boot_type(state, state->Collection, state->Any, 0, false, true, false, true);
    lisp_boot_type(state, state->Indexed, state->Collection, 0, false, true, false, true);
    lisp_boot_type(state, state->Keyed, state->Collection, 0, false, true, false, true);

    lisp_boot_type(state, state->List, state->Indexed, 3 * ptr_size, true, false, false, true);
    lisp_boot_type(state, state->ListNode, state->Any, 2 * ptr_size, false, false, false, true);
    lisp_boot_type(state, state->Vector, state->Indexed, 4 * ptr_size, true, false, false, true);
    lisp_boot_type(state, state->VectorNode, state->Any, LISP_VECTOR_SIZE * ptr_size, false, false, false, true);
    lisp_boot_type(state, state->Map, state->Keyed, ptr_size, true, false, false, true);

    lisp_boot_type(state, state->Callable, state->Any, 0, false, true, false, true);
    lisp_boot_type(state, state->Native, state->Callable, 1 * ptr_size, false, false, false, true);
    lisp_boot_type(state, state->Function, state->Callable, 5 * ptr_size, false, false, false, true);
    lisp_boot_type(state, state->Macro, state->Callable, 5 * ptr_size, false, false, false, true);

    lisp_boot_type(state, state->Char, state->Unsigned, 4, false, false, true, true);
    lisp_boot_type(state, state->Symbol, state->Any, 1 * ptr_size, false, false, false, true);
    lisp_boot_type(state, state->Keyword, state->Any, 1 * ptr_size, false, false, false, true);

    lisp_boot_type(state, state->Number, state->Any, 0, false, true, false, true);
    lisp_boot_type(state, state->Real, state->Number, 0, false, true, false, true);
    lisp_boot_type(state, state->Float, state->Real, 0, false, true, false, true);
    lisp_boot_type(state, state->Integer, state->Real, 0, false, true, false, true);
    lisp_boot_type(state, state->Signed, state->Integer, 0, false, true, false, true);
    lisp_boot_type(state, state->Unsigned, state->Integer, 0, false, true, false, true);

    lisp_boot_type(state, state->Float32, state->Float, 4, false, false, true, true);
    lisp_boot_type(state, state->Float64, state->Float, 8, false, false, true, true);

    lisp_boot_type(state, state->UInt8, state->Unsigned, 1, false, false, true, true);
    lisp_boot_type(state, state->UInt16, state->Unsigned, 2, false, false, true, true);
    lisp_boot_type(state, state->UInt32, state->Unsigned, 4, false, false, true, true);
    lisp_boot_type(state, state->UInt64, state->Unsigned, 8, false, false, true, true);

    lisp_boot_type(state, state->Int8, state->Signed, 1, false, false, true, true);
    lisp_boot_type(state, state->Int16, state->Signed, 2, false, false, true, true);
    lisp_boot_type(state, state->Int32, state->Signed, 4, false, false, true, true);
    lisp_boot_type(state, state->Int64, state->Signed, 8, false, false, true, true);

    lisp_boot_type(state, state->Bool, state->Unsigned, 1, false, false, true, true);

    lisp_boot_type(state, state->AnyList, state->Indexed, 3 * ptr_size, false, false, false, true);

    lisp_boot_type(state, state->AnyVector, state->Indexed, 4 * ptr_size, false, false, false, true);
    lisp_boot_type(state, state->CharVector, state->Indexed, 4 * ptr_size, false, false, false, true);
    lisp_boot_type(state, state->SymbolVector, state->Indexed, 4 * ptr_size, false, false, false, true);
    lisp_boot_type(state, state->AnnotationVector, state->Indexed, 4 * ptr_size, false, false, false, true);

    lisp_boot_type(state, state->AnnotationVector, state->Indexed, 4 * ptr_size, false, false, false, true);

    lisp_boot_type(state, state->AnyCallableMap, state->Keyed, ptr_size, false, false, false, true);
    lisp_boot_type(state, state->SymbolAnnotationMap, state->Keyed, ptr_size, false, false, false, true);
}

static void lisp_boot_type (
    lisp_State* state,
    lisp_Object* type,
    lisp_Object* super,
    uintsize size,
    bool template,
    bool abstract,
    bool bytes,
    bool immutable
) {
    lisp_Object** values = (lisp_Object**) type->data;
    uintsize ptr_size = sizeof(void*);

    lisp_Object* size_object = lisp_Number_new_UInt(state, size);

    if (!bytes) {
        values[LISP_IDX_TYPE_ATTRIBUTES] = lisp_Vector_init(state, lisp_boot_object_size(state, state->SymbolVector, ptr_size * 4));
        values[LISP_IDX_TYPE_TYPES] = lisp_Vector_init(state, lisp_boot_object_size(state, state->AnnotationVector, ptr_size * 4));
    }

    values[LISP_IDX_TYPE_PROTOTYPE] = lisp_Map_init(state, lisp_boot_object_size(state, state->AnyCallableMap, ptr_size));

    if (template) {
        values[LISP_IDX_TYPE_TEMPLATE] = lisp_Vector_init(state, lisp_boot_object_size(state, state->SymbolVector, ptr_size * 4));
    } else {
        values[LISP_IDX_TYPE_TEMPLATE] = state->nil;
    }

    values[LISP_IDX_TYPE_NAME] = state->nil;
    values[LISP_IDX_TYPE_SIZE] = size_object;
    values[LISP_IDX_TYPE_SUPER] = super;
    values[LISP_IDX_TYPE_ABSTRACT] = abstract ? state->tru : state->fal;
    values[LISP_IDX_TYPE_BYTES] = bytes ? state->tru : state->fal;
    values[LISP_IDX_TYPE_IMMUTABLE] = immutable ? state->tru : state->fal;
    values[LISP_IDX_TYPE_SUB_TYPES] = state->nil;
}

static lisp_Object* lisp_boot_object_alloc(lisp_State* state, lisp_Object* type) {
    lisp_GCHeader* gc_header = lisp_State_alloc(state, sizeof(lisp_Object));
    lisp_Object* object = (lisp_Object*) gc_header->data;
    lisp_boot_object_init(object, gc_header, type);
    return object;
}
static lisp_Object* lisp_boot_object_init(lisp_Object* object, lisp_GCHeader* gc_header, lisp_Object* type) {
    object->gc_header = gc_header;
    object->data = NULL;
    object->type = type;
    return object;
}
static lisp_Object* lisp_boot_object_size(lisp_State* state, lisp_Object* type, uintsize size) {
    lisp_Object* object = lisp_boot_object_alloc(state, type);
    object->data = lisp_State_assoc(state, object->gc_header, size);
    return object;
}


#endif
