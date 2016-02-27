#ifndef __LISP_BOOT_C__
#define __LISP_BOOT_C__


static void lisp_boot(lisp_State* state) {
    uintsize ptr_size = sizeof(void*);

    lisp_boot_type(state, "Type", state->Type, state->nil, LISP_TYPE_SIZE * ptr_size, false, false, false, true);

    lisp_boot_type(state, "Any", state->Any, state->nil, 0, false, true, false, true);
    lisp_boot_type(state, "Nil", state->Nil, state->Any, 0, false, false, false, true);
    lisp_boot_type(state, "Annotation", state->Annotation, state->Any, 2 * ptr_size, false, false, false, true);

    lisp_boot_type(state, "Collection", state->Collection, state->Any, 0, false, true, false, true);
    lisp_boot_type(state, "Indexed", state->Indexed, state->Collection, 0, false, true, false, true);
    lisp_boot_type(state, "Keyed", state->Keyed, state->Collection, 0, false, true, false, true);

    lisp_boot_type(state, "List", state->List, state->Indexed, 3 * ptr_size, true, false, false, true);
    lisp_boot_type(state, "ListNode", state->ListNode, state->Any, 2 * ptr_size, false, false, false, true);
    lisp_boot_type(state, "Vector", state->Vector, state->Indexed, 4 * ptr_size, true, false, false, true);
    lisp_boot_type(state, "VectorNode", state->VectorNode, state->Any, LISP_VECTOR_SIZE * ptr_size, false, false, false, true);
    lisp_boot_type(state, "Map", state->Map, state->Keyed, ptr_size, true, false, false, true);

    lisp_boot_type(state, "Callable", state->Callable, state->Any, 0, false, true, false, true);
    lisp_boot_type(state, "Native", state->Native, state->Callable, 1 * ptr_size, false, false, false, true);
    lisp_boot_type(state, "Function", state->Function, state->Callable, 5 * ptr_size, false, false, false, true);
    lisp_boot_type(state, "Macro", state->Macro, state->Callable, 5 * ptr_size, false, false, false, true);

    lisp_boot_type(state, "Char", state->Char, state->Unsigned, 4, false, false, true, true);
    lisp_boot_type(state, "Symbol", state->Symbol, state->Any, 1 * ptr_size, false, false, false, true);
    lisp_boot_type(state, "Keyword", state->Keyword, state->Any, 1 * ptr_size, false, false, false, true);

    lisp_boot_type(state, "Number", state->Number, state->Any, 0, false, true, false, true);
    lisp_boot_type(state, "Real", state->Real, state->Number, 0, false, true, false, true);
    lisp_boot_type(state, "Float", state->Float, state->Real, 0, false, true, false, true);
    lisp_boot_type(state, "Integer", state->Integer, state->Real, 0, false, true, false, true);
    lisp_boot_type(state, "Signed", state->Signed, state->Integer, 0, false, true, false, true);
    lisp_boot_type(state, "Unsigned", state->Unsigned, state->Integer, 0, false, true, false, true);

    lisp_boot_type(state, "Float32", state->Float32, state->Float, 4, false, false, true, true);
    lisp_boot_type(state, "Float64", state->Float64, state->Float, 8, false, false, true, true);

    lisp_boot_type(state, "UInt8", state->UInt8, state->Unsigned, 1, false, false, true, true);
    lisp_boot_type(state, "UInt16", state->UInt16, state->Unsigned, 2, false, false, true, true);
    lisp_boot_type(state, "UInt32", state->UInt32, state->Unsigned, 4, false, false, true, true);
    lisp_boot_type(state, "UInt64", state->UInt64, state->Unsigned, 8, false, false, true, true);

    lisp_boot_type(state, "Int8", state->Int8, state->Signed, 1, false, false, true, true);
    lisp_boot_type(state, "Int16", state->Int16, state->Signed, 2, false, false, true, true);
    lisp_boot_type(state, "Int32", state->Int32, state->Signed, 4, false, false, true, true);
    lisp_boot_type(state, "Int64", state->Int64, state->Signed, 8, false, false, true, true);

    lisp_boot_type(state, "Bool", state->Bool, state->Unsigned, 1, false, false, true, true);
    lisp_boot_type(state, "Reader", state->Reader, state->Any, 4 * ptr_size, false, false, false, true);

    lisp_boot_type(state, "List", state->AnyList, state->Indexed, 3 * ptr_size, false, false, false, true);

    lisp_boot_type(state, "Vector", state->AnyVector, state->Indexed, 4 * ptr_size, false, false, false, true);
    lisp_boot_type(state, "Vector", state->CharVector, state->Indexed, 4 * ptr_size, false, false, false, true);
    lisp_boot_type(state, "Vector", state->SymbolVector, state->Indexed, 4 * ptr_size, false, false, false, true);
    lisp_boot_type(state, "Vector", state->AnnotationVector, state->Indexed, 4 * ptr_size, false, false, false, true);
    
    lisp_boot_type(state, "Map", state->AnyAnyMap, state->Keyed, ptr_size, false, false, false, true);
    lisp_boot_type(state, "Map", state->AnyCallableMap, state->Keyed, ptr_size, false, false, false, true);
    lisp_boot_type(state, "Map", state->SymbolAnnotationMap, state->Keyed, ptr_size, false, false, false, true);
    lisp_boot_type(state, "Map", state->AnnotationTypeMap, state->Keyed, ptr_size, false, false, false, true);

    lisp_Type_boot(state, state->Type);
}

static void lisp_boot_type (
    lisp_State* state,
    char* name,
    lisp_Object* type,
    lisp_Object* super,
    uintsize size,
    bool template,
    bool abstract,
    bool bytes,
    bool immutable
) {
    lisp_Object** values = (lisp_Object**) type->data;

    values[LISP_IDX_TYPE_NAME] = lisp_Vector_from_ascii(state, name);

    if (!bytes) {
        values[LISP_IDX_TYPE_ATTRIBUTES] = lisp_Vector_new_type(state, state->SymbolVector);
        values[LISP_IDX_TYPE_TYPES] = lisp_Vector_new_type(state, state->AnnotationVector);
    }

    values[LISP_IDX_TYPE_PROTOTYPE] = lisp_Map_new_type(state, state->AnyCallableMap);

    if (template) {
        values[LISP_IDX_TYPE_TEMPLATE] = lisp_Vector_new_type(state, state->SymbolVector);
        values[LISP_IDX_TYPE_SUBTYPES] = lisp_Map_new_type(state, state->AnnotationTypeMap);
    } else {
        values[LISP_IDX_TYPE_TEMPLATE] = state->nil;
        values[LISP_IDX_TYPE_SUBTYPES] = state->nil;
    }

    values[LISP_IDX_TYPE_SIZE] = lisp_Number_new_UInt(state, size);
    values[LISP_IDX_TYPE_SUPER] = super;
    values[LISP_IDX_TYPE_ABSTRACT] = abstract ? state->tru : state->fal;
    values[LISP_IDX_TYPE_BYTES] = bytes ? state->tru : state->fal;
    values[LISP_IDX_TYPE_IMMUTABLE] = immutable ? state->tru : state->fal;
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
