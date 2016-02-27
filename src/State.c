#ifndef __LISP_STATE_C__
#define __LISP_STATE_C__


lisp_State* lisp_State_new(void) {
    lisp_State* state = (lisp_State*) malloc(sizeof(lisp_State));
    state->gc = lisp_GC_new();

    uintsize sizeof_values = sizeof(lisp_Object**) * LISP_TYPE_SIZE;

    state->Type = lisp_boot_object_size(state, NULL, sizeof_values);
    state->Type->type = state->Type;

    state->Any = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Nil = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Annotation = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->Collection = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Indexed = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Keyed = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->List = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->ListNode = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Vector = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->VectorNode = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Map = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->Callable = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Native = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Function = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Macro = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->Char = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Symbol = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Keyword = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->Number = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Real = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Float = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Integer = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Signed = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Unsigned = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->Float32 = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Float64 = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->UInt8 = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->UInt16 = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->UInt32 = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->UInt64 = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->Int8 = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Int16 = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Int32 = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Int64 = lisp_boot_object_size(state, state->Type, sizeof_values);

    if (sizeof(uintsize) < 8) {
        state->UInt = state->UInt32;
        state->Int = state->Int32;
    } else {
        state->UInt = state->UInt64;
        state->Int = state->Int64;
    }

    state->Bool = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->Reader = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->nil = lisp_boot_object_alloc(state, state->Nil);
    state->tru = lisp_boot_object_size(state, state->Bool, 1);
    state->fal = lisp_boot_object_size(state, state->Bool, 1);

    state->AnyList = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->AnyVector = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->CharVector = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->SymbolVector = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->AnnotationVector = lisp_boot_object_size(state, state->Type, sizeof_values);

    state->AnyAnyMap = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->AnyCallableMap = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->SymbolAnnotationMap = lisp_boot_object_size(state, state->Type, sizeof_values);
    state->AnnotationTypeMap = lisp_boot_object_size(state, state->Type, sizeof_values);

    LISP_OBJECT_SET_DATA(state->tru, bool, true);
    LISP_OBJECT_SET_DATA(state->fal, bool, false);

    lisp_boot(state);

    return state;
}
void lisp_State_delete(lisp_State* state) {
    lisp_GC_delete(state->gc);
    free(state);
}

lisp_GCHeader* lisp_State_alloc(lisp_State* state, uintsize bytes) {
    return lisp_GC_alloc(state->gc, bytes);
}
void lisp_State_dealloc(lisp_State* state, lisp_GCHeader* gc_header) {
    lisp_GC_dealloc(state->gc, gc_header);
}

void* lisp_State_assoc(lisp_State* state, lisp_GCHeader* gc_header, uintsize bytes) {
    return lisp_GCHeader_assoc(state->gc, gc_header, bytes);
}
void lisp_State_dissoc(lisp_State* state, lisp_GCHeader* gc_header, void* data) {
    lisp_GCHeader_dissoc(state->gc, gc_header, data);
}


#endif
