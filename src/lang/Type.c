#ifndef __LISP_LANG_TYPE_C__
#define __LISP_LANG_TYPE_C__


static void lisp_Type_constructor(
    lisp_Type* type,
    lisp_Value* name,
    lisp_Value* attributes,
    lisp_Value* types,
    lisp_Value* prototype,
    lisp_Value* template,
    lisp_Value* super,
    void (*alloc)(lisp_State*, lisp_Value*),
    void (*dealloc)(lisp_State*, lisp_Value*)
) {
    type->name = name;
    type->attributes = attributes;
    type->types = types;
    type->prototype = prototype;
    type->template = template;
    type->super = super;

    if (alloc != NULL) {
        type->alloc = alloc;
    }
    if (dealloc != NULL) {
        type->dealloc = dealloc;
    }
}

static lisp_bool lisp_Type_inherits(lisp_Value* child, lisp_Value* parent) {
    if (child->type == parent->type) {
        return LISP_TRUE;
    } else {
        lisp_Type* type = (lisp_Type*) child->type->value;

        if (type->super == NULL) {
            return LISP_FALSE;
        } else {
            return lisp_Type_inherits(type->super, parent);
        }
    }
}

static void lisp_Type_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Type* type = (lisp_Type*) lisp_State_alloc(state, sizeof(lisp_Type));
    value->value = type;
}
static void lisp_Type_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Type* type = (lisp_Type*) value->value;

    if (type->name != NULL) {
        lisp_Value_deref(state, type->name);
    }
    if (type->attributes != NULL) {
        lisp_Value_deref(state, type->attributes);
    }
    if (type->types != NULL) {
        lisp_Value_deref(state, type->types);
    }
    if (type->prototype != NULL) {
        lisp_Value_deref(state, type->prototype);
    }
    if (type->template != NULL) {
        lisp_Value_deref(state, type->template);
    }
    if (type->super != NULL) {
        lisp_Value_deref(state, type->super);
    }
}


#endif
