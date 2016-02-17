#ifndef __LISP_CORE_STATE_C__
#define __LISP_CORE_STATE_C__


lisp_State* lisp_State_new(void) {
    uintsize sizeof_Type = sizeof(lisp_Type);

    lisp_State* state = (lisp_State*) malloc(sizeof(lisp_State));
    state->gc = lisp_GC_new();

    state->Type = lisp_Object_boot_size(state, NULL, sizeof_Type);
    state->Type->type = state->Type;

    state->Any = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Nil = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Annotation = lisp_Object_boot_size(state, state->Type, sizeof_Type);

    state->Collection = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Indexed = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Keyed = lisp_Object_boot_size(state, state->Type, sizeof_Type);

    state->List = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Vector = lisp_Object_boot_size(state, state->Type, sizeof_Type);

    state->Callable = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Native = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Function = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Macro = lisp_Object_boot_size(state, state->Type, sizeof_Type);

    state->Char = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Symbol = lisp_Object_boot_size(state, state->Type, sizeof_Type);

    state->Number = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Real = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Float = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Integer = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Signed = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Unsigned = lisp_Object_boot_size(state, state->Type, sizeof_Type);

    state->Float32 = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Float64 = lisp_Object_boot_size(state, state->Type, sizeof_Type);

    state->UInt8 = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->UInt16 = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->UInt32 = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->UInt64 = lisp_Object_boot_size(state, state->Type, sizeof_Type);

    state->Int8 = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Int16 = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Int32 = lisp_Object_boot_size(state, state->Type, sizeof_Type);
    state->Int64 = lisp_Object_boot_size(state, state->Type, sizeof_Type);

    if (sizeof(uintsize) < 8) {
        state->UInt = state->UInt32;
        state->Int = state->Int32;
    } else {
        state->UInt = state->UInt64;
        state->Int = state->Int64;
    }

    state->Bool = lisp_Object_boot_size(state, state->Type, sizeof_Type);

    state->nil_value = lisp_Object_boot_alloc(state, state->Nil);
    state->true_value = lisp_Object_boot_size(state, state->Bool, 1);
    state->false_value = lisp_Object_boot_size(state, state->Bool, 1);

    LISP_OBJECT_SET_DATA(state->true_value, bool, true);
    LISP_OBJECT_SET_DATA(state->false_value, bool, false);

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
