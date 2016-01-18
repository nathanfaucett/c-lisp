static lisp_Value* list(lisp_State* state, lisp_Value* params, lisp_Scope* scope) {
    return params;
}

static lisp_Value* list_get(lisp_State* state, lisp_Value* params, lisp_Scope* scope) {
    lisp_Value* list = lisp_List_get(state, &params->list, 0);
    lisp_Value* index = lisp_List_get(state, &params->list, 1);
    return lisp_List_get(state, &list->list, lisp_Number_get_i32(&index->number));
}

static lisp_Value* equal(lisp_State* state, lisp_Value* params, lisp_Scope* scope) {
    return lisp_Value_boolean(state,
        lisp_Value_equal(
            lisp_List_get(state, &params->list, 0),
            lisp_List_get(state, &params->list, 1)
        )
    );
}

static lisp_Value* Number_mul(lisp_State* state, lisp_Value* params, lisp_Scope* scope) {
    lisp_Value* a = lisp_List_get(state, &params->list, 0);
    lisp_Value* b = lisp_List_get(state, &params->list, 1);

    if (a->type == b->type && a->type == LISP_TYPE_NUMBER) {
        if (a->number.is_f64 || b->number.is_f64) {
            return lisp_Value_number_from_f64(state,
                lisp_Number_get_f64(&a->number) * lisp_Number_get_f64(&b->number)
            );
        } else {
            return lisp_Value_number_from_i32(state,
                lisp_Number_get_i32(&a->number) * lisp_Number_get_i32(&b->number)
            );
        }
    } else {
        return lisp_Value_number_from_i32(state, 0);
    }
}

static lisp_Value* Number_sub(lisp_State* state, lisp_Value* params, lisp_Scope* scope) {
    lisp_Value* a = lisp_List_get(state, &params->list, 0);
    lisp_Value* b = lisp_List_get(state, &params->list, 1);

    if (a->type == b->type && a->type == LISP_TYPE_NUMBER) {
        if (a->number.is_f64 || b->number.is_f64) {
            return lisp_Value_number_from_f64(state,
                lisp_Number_get_f64(&a->number) - lisp_Number_get_f64(&b->number)
            );
        } else {
            return lisp_Value_number_from_i32(state,
                lisp_Number_get_i32(&a->number) - lisp_Number_get_i32(&b->number)
            );
        }
    } else {
        return lisp_Value_number_from_i32(state, 0);
    }
}
