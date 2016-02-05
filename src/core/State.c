#ifndef __LISP_CORE_STATE_C__
#define __LISP_CORE_STATE_C__


static lisp_State* lisp_State_new(void) {
    lisp_State* state = (lisp_State*) malloc(sizeof(lisp_State));
    state->gc = lisp_GC_new();

    lisp_size sizeof_Type = sizeof(lisp_Type);
    state->Type = lisp_boot_new_size(state, NULL, sizeof_Type, LISP_TRUE);

    state->Annotation = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    state->Any = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Nil = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    state->Collection = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Indexed = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Keyed = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    state->MutableList = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->MutableMap = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    state->Callable = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Native = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Function = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Macro = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    state->Char = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->String = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Symbol = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    state->Number = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Real = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Float = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Integer = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Signed = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Unsigned = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    state->Float32 = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Float64 = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    state->UInt8 = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->UInt16 = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->UInt32 = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->UInt64 = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    state->Int8 = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Int16 = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Int32 = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);
    state->Int64 = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    if (sizeof(lisp_size) == 8) {
        state->UInt = state->UInt64;
        state->Int = state->Int64;
    } else {
        state->UInt = state->UInt32;
        state->Int = state->Int32;
    }

    state->Bool = lisp_boot_new_size(state, state->Type, sizeof_Type, LISP_TRUE);

    state->nil = lisp_boot_new_size(state, state->Nil, 0, LISP_TRUE);

    lisp_boot(state);

    return state;
}
static void lisp_State_delete(lisp_State* state) {
    lisp_GC_delete(state->gc);
    free(state);
}

static lisp_GCNode* lisp_State_static_alloc(lisp_State* state, lisp_size size) {
    return lisp_GC_static_alloc(state->gc, size);
}
static lisp_GCNode* lisp_State_alloc(lisp_State* state, lisp_size size) {
    return lisp_GC_alloc(state->gc, size);
}
static void lisp_State_dealloc(lisp_State* state, void* object) {
    lisp_GC_dealloc(state->gc, object);
}

static void* lisp_State_assoc(lisp_State* state, lisp_GCNode* gc_node, lisp_size size) {
    return lisp_GCNode_assoc(state->gc, gc_node, size);
}
static void lisp_State_dissoc(lisp_State* state, lisp_GCNode* gc_node, void* object) {
    lisp_GCNode_dissoc(state->gc, gc_node, object);
}


#endif
