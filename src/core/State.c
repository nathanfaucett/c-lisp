#ifndef __LISP_CORE_STATE_C__
#define __LISP_CORE_STATE_C__


static lisp_State* lisp_State_new(void) {
    lisp_size sizeof_Type = sizeof(lisp_Type);

    lisp_State* state = (lisp_State*) malloc(sizeof(lisp_State));

    state->heap = lisp_Heap_new();

    state->Type = lisp_boot_new_size(state, NULL, sizeof_Type);

    state->Annotation = lisp_boot_new_size(state, state->Type, sizeof_Type);

    state->Any = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Nil = lisp_boot_new_size(state, state->Type, sizeof_Type);

    state->Collection = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Indexed = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Keyed = lisp_boot_new_size(state, state->Type, sizeof_Type);

    state->Array = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Map = lisp_boot_new_size(state, state->Type, sizeof_Type);

    state->Callable = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Native = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Function = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Macro = lisp_boot_new_size(state, state->Type, sizeof_Type);

    state->Char = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->String = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Symbol = lisp_boot_new_size(state, state->Type, sizeof_Type);

    state->Number = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Real = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Float = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Integer = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Signed = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Unsigned = lisp_boot_new_size(state, state->Type, sizeof_Type);

    state->Float32 = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Float64 = lisp_boot_new_size(state, state->Type, sizeof_Type);

    state->UInt8 = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->UInt16 = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->UInt32 = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->UInt64 = lisp_boot_new_size(state, state->Type, sizeof_Type);

    state->Int8 = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Int16 = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Int32 = lisp_boot_new_size(state, state->Type, sizeof_Type);
    state->Int64 = lisp_boot_new_size(state, state->Type, sizeof_Type);

    if (sizeof(lisp_size) == 8) {
        state->UInt = state->UInt64;
        state->Int = state->Int64;
    } else {
        state->UInt = state->UInt32;
        state->Int = state->Int32;
    }

    state->Bool = lisp_boot_new_size(state, state->Type, sizeof_Type);

    state->nil = lisp_boot_new_size(state, state->Nil, 0);

    state->true = lisp_boot_new_size(state, state->Bool, 1);
    LISP_SET_DATA(state->true , lisp_bool, LISP_TRUE);
    state->false = lisp_boot_new_size(state, state->Bool, 1);
    LISP_SET_DATA(state->true , lisp_bool, LISP_TRUE);

    lisp_boot(state);

    return state;
}
static void lisp_State_delete(lisp_State* state) {
    lisp_Heap_delete(state->heap);
}

static void* lisp_State_alloc(lisp_State* state, size_t size) {
    return lisp_Heap_alloc(state->heap, size);
}
static void lisp_State_dealloc(lisp_State* state, void* value) {
    lisp_Heap_dealloc(state->heap, value);
}


#endif
