#ifndef __LISP_LANG_VALUE_C__
#define __LISP_LANG_VALUE_C__


static lisp_Value* lisp_Value_alloc(lisp_State* state, lisp_Value* Type) {
    lisp_Value* value = lisp_State_alloc(state, sizeof(lisp_Value));
    lisp_Type* type = (lisp_Type*) Type->data;
    lisp_Array* type_values = (lisp_Array*) Type->values->data;

    value->marked = LISP_FALSE;
    value->type = Type;

    lisp_Value* size_value = lisp_Array_get(state, type_values, LISP_IDX_TYPE_SIZE);
    lisp_size size = LISP_GET_DATA(size_value, lisp_size);
    if (size != 0) {
        value->data = lisp_State_alloc(state, size);
    } else {
        value->data = NULL;
    }

    lisp_Value* attributes_value = lisp_Array_get(state, type_values, LISP_IDX_TYPE_ATTRIBUTES);
    lisp_Value* values = lisp_boot_new_array(state);
    lisp_Array_set_size(state, (lisp_Array*) values->data, ((lisp_Array*) attributes_value->data)->size);
    value->values = values;

    if (type->alloc != NULL) {
        type->alloc(state, value);
    }

    return value;
}
static void lisp_Value_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Type* type = (lisp_Type*) value->type->data;

    if (type->dealloc != NULL) {
        type->dealloc(state, value);
    }

    lisp_State_dealloc(state, value);
}
static void lisp_Value_mark(lisp_Value* value) {
    if (value->marked == LISP_FALSE) {
        lisp_Type* type = (lisp_Type*) value->type->data;

        value->marked = LISP_TRUE;

        if (value->type != NULL) {
            lisp_Value_mark(value->type);
        }
        if (value->values != NULL) {
            lisp_Value_mark(value->values);
        }
        if (value->template != NULL) {
            lisp_Value_mark(value->template);
        }


        if (type->mark != NULL) {
            type->mark(value);
        }
    }
}

static lisp_Value* lisp_Value_lookup(lisp_State* state, lisp_Value* object, lisp_Value* type, lisp_Value* key) {
    lisp_size index = lisp_Array_index_of(state, (lisp_Array*) type->values->data, key);

    if (index == 0) {
        lisp_Value* super = lisp_Array_get(state, (lisp_Array*) type->values->data, LISP_IDX_TYPE_SUPER);

        if (super != state->nil) {
            return lisp_Value_lookup(state, object, super, key);
        } else {
            return state->nil;
        }
    } else {
        return lisp_Array_get(state, (lisp_Array*) object->values->data, index);
    }
}

static lisp_Value* lisp_Value_function_call(lisp_State* state, lisp_Value* fn, lisp_Value* args, lisp_Scope* scope) {
    lisp_Value* type = fn->type;

    if (type == state->Function) {
        return lisp_Function_call(state, fn, args, scope);
    } else if (type == state->Macro) {
        return lisp_Macro_call(state, fn, args, scope);
    } else if (type == state->Native) {
        return lisp_Native_call(state, fn, args, scope);
    } else {
        return lisp_Value_call1(state, fn, lisp_Symbol_from_ascii(state, "call"), args, scope);
    }
}

static lisp_Value* lisp_Value_call1(lisp_State* state, lisp_Value* object, lisp_Value* key, lisp_Value* a0, lisp_Scope* scope) {
    lisp_Value* fn = lisp_Value_lookup(state, object, object->type, key);

    if (lisp_Value_inherits(state, fn->type, state->Callable)) {
        lisp_Value* args = lisp_Value_alloc(state, state->Array);
        lisp_Array* array = (lisp_Array*) args->data;
        lisp_Array_push(array, object);
        lisp_Array_push(array, a0);
        return lisp_Value_function_call(state, fn, args, scope);
    } else {
        return state->nil;
    }
}

static lisp_bool lisp_Value_inherits(lisp_State* state, lisp_Value* a, lisp_Value* b) {
    if (a == b) {
        return LISP_TRUE;
    } else {
        lisp_Value* super = lisp_Array_get(state, (lisp_Array*) a->values->data, LISP_IDX_TYPE_SUPER);

        if (super != state->nil) {
            return lisp_Value_inherits(state, super, b);
        } else {
            return LISP_FALSE;
        }
    }
}

static lisp_bool lisp_Value_equal(lisp_State* state, lisp_Value* a, lisp_Value* b) {
    return a == b;
}


#endif
