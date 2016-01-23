#ifndef __LISP_LANG_TYPE_C__
#define __LISP_LANG_TYPE_C__


static void lisp_Type_constructor(
    lisp_Type* type,
    lisp_Value* name,
    lisp_Value* parameters,
    lisp_Value* types,
    lisp_Value* methods,
    lisp_Value* super,
    void (*alloc)(lisp_State*, lisp_Value*),
    void (*dealloc)(lisp_State*, lisp_Value*)
) {
    type->name = name;
    type->parameters = parameters;
    type->types = types;
    type->methods = methods;
    type->super = super;

    if (alloc != NULL) {
        type->alloc = alloc;
    } else {
        type->alloc = lisp_Type_default_alloc;
    }

    if (dealloc != NULL) {
        type->dealloc = dealloc;
    } else {
        type->dealloc = lisp_Type_default_dealloc;
    }
}

static void lisp_Type_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Type* type = (lisp_Type*) lisp_State_alloc(state, sizeof(lisp_Type));
    value->value = type;
}
static void lisp_Type_dealloc(lisp_State* state, lisp_Value* value) {
    /* nothing to delete */
}

static void lisp_Type_empty_alloc(lisp_State* state, struct lisp_Value* value) {
    /* empty */
}
static void lisp_Type_empty_dealloc(lisp_State* state, struct lisp_Value* value) {
    /* empty */
}

static void lisp_Type_default_alloc(lisp_State* state, lisp_Value* value) {
    value->values = lisp_Value_new(state, state->type_list);
}
static void lisp_Type_default_dealloc(lisp_State* state, lisp_Value* value) {
    if (value->values != NULL) {
        lisp_Value_delete(state, value->values);
    }
}


#endif
