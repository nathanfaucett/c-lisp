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

static lisp_bool lisp_Value_equal(lisp_State* state, lisp_Value* a, lisp_Value* b) {
    if (a->type == b->type) {
        if (a->type == state->Map) {
            return lisp_Map_equal(state, (lisp_Map*) a->data, (lisp_Map*) b->data);
        } else if (a->type == state->Seq) {
            return lisp_Seq_equal(state, (lisp_Seq*) a->data, (lisp_Seq*) b->data);
        } else {
            return LISP_TRUE;
        }
    } else {
        return LISP_FALSE;
    }
}

static lisp_bool lisp_Value_find_method() {

}

static lisp_bool lisp_Value_call_arg0(lisp_State* state, lisp_Value* object, lisp_Value* key) {

}


#endif
