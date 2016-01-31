#ifndef __LISP_BOOT_C__
#define __LISP_BOOT_C__


static void lisp_boot(lisp_State* state) {
    state->Type = lisp_boot_create_MainType(state);

    state->Any = lisp_boot_create_BootType(state, NULL, 0, NULL, NULL, NULL);
    state->Nil = lisp_boot_create_BootType(state, state->Any, 0, NULL, NULL, NULL);

    state->Bool = lisp_boot_create_BootType(state, state->Any, 1, NULL, NULL, NULL);
    state->Char = lisp_boot_create_BootType(state, state->Any, 4, NULL, NULL, NULL);
    state->String = lisp_boot_create_BootType(state, NULL, sizeof(lisp_String), lisp_String_alloc, lisp_String_dealloc, lisp_String_mark);
    state->Symbol = lisp_boot_create_BootType(state, state->Any, sizeof(lisp_Symbol), lisp_Symbol_alloc, NULL, lisp_Symbol_mark);

    state->MutableMap = lisp_boot_create_BootType(state, NULL, sizeof(lisp_MutableMap), lisp_MutableMap_alloc, lisp_MutableMap_dealloc, lisp_MutableMap_mark);
    state->Seq = lisp_boot_create_BootType(state, NULL, sizeof(lisp_Seq), lisp_Seq_alloc, lisp_Seq_dealloc, lisp_Seq_mark);

    state->List = lisp_boot_create_BootType(state, NULL, sizeof(lisp_List), lisp_List_alloc, NULL, lisp_List_mark);
    state->ListNode = lisp_boot_create_BootType(state, NULL, sizeof(lisp_ListNode), lisp_ListNode_alloc, NULL, lisp_ListNode_mark);

    lisp_boot_create_InitType(state, state->Type, "Type", LISP_FALSE, LISP_FALSE);

    lisp_boot_create_InitType(state, state->Any, "Any", LISP_TRUE, LISP_FALSE);
    lisp_boot_create_InitType(state, state->Nil, "Nil", LISP_FALSE, LISP_FALSE);

    lisp_boot_create_InitType(state, state->Bool, "Bool", LISP_FALSE, LISP_TRUE);
    lisp_boot_create_InitType(state, state->Char, "Char", LISP_FALSE, LISP_TRUE);
    lisp_boot_create_InitType(state, state->String, "String", LISP_FALSE, LISP_FALSE);
    lisp_boot_create_InitType(state, state->Symbol, "Symbol", LISP_FALSE, LISP_FALSE);

    lisp_boot_create_InitType(state, state->MutableMap, "Map", LISP_FALSE, LISP_FALSE);
    lisp_boot_create_InitType(state, state->Seq, "Seq", LISP_FALSE, LISP_FALSE);

    lisp_boot_create_InitType(state, state->List, "List", LISP_FALSE, LISP_FALSE);
    lisp_boot_create_InitType(state, state->ListNode, "ListNode", LISP_FALSE, LISP_FALSE);

    lisp_boot_core(state);
}

static lisp_Value* lisp_boot_create_MainType(lisp_State* state) {
    lisp_size size = sizeof(lisp_Type);
    lisp_Type* type = (lisp_Type*) malloc(size);
    lisp_Value* value = lisp_State_alloc(state, sizeof(lisp_Value));

    type->size = size;
    type->super = NULL;
    type->alloc = NULL;
    type->dealloc = NULL;
    type->mark = NULL;

    value->type = value;
    value->data = type;

    return value;
}

static lisp_Value* lisp_boot_create_BootType(
    lisp_State* state,
    lisp_Value* super,
    lisp_size size,
    void (*alloc)(lisp_State*, lisp_Value*),
    void (*dealloc)(lisp_State*, lisp_Value*),
    void (*mark)(lisp_Value*)
) {
    lisp_Value* value = lisp_Value_alloc(state, state->Type);
    lisp_Type* type = (lisp_Type*) value->data;

    type->size = size;
    type->super = super;

    type->alloc = alloc;
    type->dealloc = dealloc;
    type->mark = mark;

    return value;
}

static void lisp_boot_create_InitType(
    lisp_State* state,
    lisp_Value* value,
    lisp_char* ascii,
    lisp_bool abstract,
    lisp_bool bytes
) {
    lisp_Type* type = (lisp_Type*) value->data;

    type->name = lisp_Symbol_new_ascii(state, ascii);
    type->attributes = lisp_Value_alloc(state, state->Seq);
    type->types = lisp_Value_alloc(state, state->Seq);
    type->prototype = lisp_Value_alloc(state, state->MutableMap);
    type->template = lisp_Value_alloc(state, state->MutableMap);

    type->abstract = lisp_Value_alloc(state, state->Bool);
    LISP_SET_DATA(type->abstract, lisp_bool, LISP_FALSE);

    type->bytes = lisp_Value_alloc(state, state->Bool);
    LISP_SET_DATA(type->abstract, lisp_bool, LISP_FALSE);
}

static lisp_Value* lisp_boot_create_Type(
    lisp_State* state,
    lisp_Value* super,
    lisp_size size,
    lisp_char* ascii,
    void (*alloc)(lisp_State*, lisp_Value*),
    void (*dealloc)(lisp_State*, lisp_Value*),
    void (*mark)(lisp_Value*)
) {
    lisp_Value* value = lisp_Value_alloc(state, state->Type);
    lisp_Type* type = (lisp_Type*) value->data;

    type->size = size;
    type->super = super;

    lisp_boot_create_InitType(state, value, ascii, LISP_FALSE, LISP_FALSE);

    type->alloc = alloc;
    type->dealloc = dealloc;
    type->mark = mark;

    return value;
}
static lisp_Value* lisp_boot_create_AbstractType(lisp_State* state, lisp_Value* super, lisp_char* ascii) {
    lisp_Value* value = lisp_Value_alloc(state, state->Type);
    lisp_Type* type = (lisp_Type*) value->data;

    type->size = 0;
    type->super = super;
    lisp_boot_create_InitType(state, value, ascii, LISP_TRUE, LISP_FALSE);
    type->alloc = NULL;
    type->dealloc = NULL;
    type->mark = NULL;

    return value;
}
static lisp_Value* lisp_boot_create_BytesType(lisp_State* state, lisp_Value* super, lisp_size size, lisp_char* ascii) {
    lisp_Value* value = lisp_Value_alloc(state, state->Type);
    lisp_Type* type = (lisp_Type*) value->data;

    type->size = size;
    type->super = super;
    lisp_boot_create_InitType(state, value, ascii, LISP_FALSE, LISP_TRUE);
    type->alloc = NULL;
    type->dealloc = NULL;
    type->mark = NULL;

    return value;
}


#endif
