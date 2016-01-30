#ifndef __LISP_LANG_VALUE_C__
#define __LISP_LANG_VALUE_C__


static lisp_Value* lisp_Value_alloc(lisp_State* state, lisp_Value* type_value) {
    lisp_Type* type = (lisp_Type*) type_value->data;
    lisp_Value* value = lisp_State_alloc(state, sizeof(lisp_Value));

    value->marked = LISP_FALSE;
    value->type = type_value;

    if (type->size != 0) {
        value->data = lisp_State_alloc(state, type->size);
    } else {
        value->data = NULL;
    }

    value->values = NULL;

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

        if (type->mark != NULL) {
            type->mark(value);
        }
    }
}

static lisp_Value* lisp_Value_find(lisp_State* state, lisp_Value* object, lisp_Value* key) {
    lisp_Type* type = (lisp_Type*) object->type->data;

    if (object->values != NULL) {
        lisp_Seq* attributes = (lisp_Seq*) type->attributes->data;
        lisp_size index = lisp_Seq_index_of(state, attributes, key);

        if (index != 0) {
            return lisp_Seq_get(state, (lisp_Seq*) object->values->data, index - 1);
        }
    }
    lisp_Map* prototype = (lisp_Map*) type->prototype->data;

    if (lisp_Map_has(state, prototype, key)) {
        return lisp_Map_get(state, prototype, key);
    } else if (type->super != NULL) {
        return lisp_Value_find(state, type->super, key);
    } else {
        return state->nil;
    }
}

static lisp_Value* lisp_Value_apply(lisp_State* state, lisp_Value* object, lisp_Value* key, lisp_Value* args) {
    lisp_Value* value = lisp_Value_find(state, object, key);

    if (value->type == state->Function) {
        return lisp_Function_call(state, (lisp_Function*) value->data, args, NULL);
    } else {
        return state->nil;
    }
}
static lisp_Value* lisp_Value_call(lisp_State* state, lisp_Value* object, lisp_Value* key) {
    lisp_Value* value = lisp_Value_find(state, object, key);

    if (value->type == state->Function) {
        lisp_Value* args = lisp_Value_alloc(state, state->Seq);
        lisp_Value* ret = lisp_Function_call(state, (lisp_Function*) value->data, args, NULL);
        lisp_Value_dealloc(state, args);
        return ret;
    } else {
        return state->nil;
    }
}
static lisp_Value* lisp_Value_call_arg1(lisp_State* state, lisp_Value* object, lisp_Value* key, lisp_Value* a0) {
    lisp_Value* value = lisp_Value_find(state, object, key);

    if (value->type == state->Function) {
        lisp_Value* args = lisp_Value_alloc(state, state->Seq);
        lisp_Seq_push((lisp_Seq*) args->data, a0);
        lisp_Value* ret = lisp_Function_call(state, (lisp_Function*) value->data, args, NULL);
        lisp_Value_dealloc(state, args);
        return ret;
    } else {
        return state->nil;
    }
}

static lisp_bool lisp_Value_equal(lisp_State* state, lisp_Value* a, lisp_Value* b) {
    if (a->type == b->type) {
        if (a->type == state->Map) {
            return lisp_Map_equal(state, (lisp_Map*) a->data, (lisp_Map*) b->data);
        } else if (a->type == state->Seq) {
            return lisp_Seq_equal(state, (lisp_Seq*) a->data, (lisp_Seq*) b->data);
        } else {
            lisp_Value* equal = lisp_Symbol_new_ascii(state, "equal");
            lisp_Value* value = lisp_Value_call_arg1(state, a, equal, b);
            lisp_Value_dealloc(state, equal);

            if (value->type != state->Bool) {
                return LISP_FALSE;
            } else {
                return *((lisp_bool*) value->data);
            }
        }
    } else {
        return LISP_FALSE;
    }
}


#endif
