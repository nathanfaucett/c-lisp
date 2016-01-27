#ifndef __LISP_LANG_VALUE_C__
#define __LISP_LANG_VALUE_C__


static lisp_Value* lisp_Value_alloc(lisp_State* state, lisp_Value* type) {
    lisp_Value* value = lisp_State_alloc(state, sizeof(lisp_Value));
    value->ref_count = 1;
    value->type = type;
    value->value = NULL;
    value->values = NULL;

    if (type->value != NULL) {
        lisp_Type* type_value = (lisp_Type*) type->value;

        if (type_value->alloc != NULL) {
            type_value->alloc(state, value);
        }
    }
    return value;
}
static void lisp_Value_dealloc(lisp_State* state, lisp_Value* value) {
    if (value->type != NULL) {
        lisp_Type* type_value = (lisp_Type*) value->type->value;

        if (type_value->dealloc != NULL) {
            type_value->dealloc(state, value);
        }
    }
    lisp_State_dealloc(state, value);
}

lisp_Value* lisp_Value_ref(lisp_Value* value) {
    value->ref_count += 1;
    return value;
}
void lisp_Value_deref(lisp_State* state, lisp_Value* value) {
    value->ref_count -= 1;

    if (value->ref_count == 0) {
        lisp_Value_dealloc(state, value);
    }
}

static lisp_u64 lisp_Value_map_index_of(lisp_State* state, lisp_Map* map, lisp_Value* symbol) {
    if (map->entries != NULL) {
        lisp_List* entries = (lisp_List*) map->entries->value;
        lisp_ListNode* node = entries->root;
        lisp_u64 index = 0;

        while (node != NULL) {
            lisp_Value* value = (lisp_Value*) node->value;
            index += 2;

            if (
                value->type == state->type_symbol &&
                lisp_Symbol_equal((lisp_Symbol*) symbol->value, (lisp_Symbol*) value->value)
            ) {
                return index + 1;
            }
        }

        return 0;
    } else {
        return 0;
    }
}

static lisp_Value* lisp_Value_map_get(lisp_State* state, lisp_Map* map, lisp_Value* symbol) {
    lisp_u64 index = lisp_Value_map_index_of(state, map, symbol);

    if (index != 0) {
        return lisp_List_get(state, (lisp_List*) map->entries->value, index - 1);
    } else {
        return lisp_Value_ref(state->nil);
    }
}

lisp_Map* lisp_Value_find_prototype(lisp_State* state, lisp_Value* object, lisp_Value* symbol) {
    lisp_Type* type = (lisp_Type*) object->type->value;
    lisp_Map* map = NULL;

    if (type->prototype != NULL && type->prototype->type == state->type_map) {
        map = (lisp_Map*) type->prototype->value;
    }

    if (map != NULL && lisp_Map_has(state, map, symbol) != 0) {
        return map;
    } else if (type->super != NULL) {
        return lisp_Value_find_prototype(state, type->super, symbol);
    } else {
        return NULL;
    }
}

lisp_Value* lisp_Value_call_arg0(lisp_State* state, lisp_Value* object, lisp_Value* symbol, lisp_Scope* scope) {
    lisp_Map* prototype = lisp_Value_find_prototype(state, object, symbol);
    lisp_Value* value = lisp_Map_get(state, prototype, symbol);

    if (value->type == state->type_function) {
        return lisp_Function_call(state, (lisp_Function*) value->value, state->empty_list, scope);
    } else if (value->type == state->type_macro) {
        return lisp_Macro_call(state, (lisp_Macro*) value->value, state->empty_list, scope);
    } else {
        return state->nil;
    }
}
lisp_Value* lisp_Value_call_arg1(lisp_State* state, lisp_Value* object, lisp_Value* symbol, lisp_Value* arg0, lisp_Scope* scope) {
    lisp_Map* prototype = lisp_Value_find_prototype(state, object, symbol);
    lisp_Value* value = lisp_Map_get(state, prototype, symbol);

    if (value->type == state->type_function) {
        lisp_MutList* mut_list = lisp_MutList_new();
        lisp_MutList_push(mut_list, arg0);
        lisp_Value* args = lisp_List_from_mut_list(state, mut_list);
        lisp_Value* ret = lisp_Function_call(state, (lisp_Function*) value->value, args, scope);
        lisp_MutList_delete(mut_list);
        return ret;
    } else if (value->type == state->type_macro) {
        lisp_MutList* mut_list = lisp_MutList_new();
        lisp_MutList_push(mut_list, arg0);
        lisp_Value* args = lisp_List_from_mut_list(state, mut_list);
        lisp_Value* ret = lisp_Macro_call(state, (lisp_Macro*) value->value, args, scope);
        lisp_MutList_delete(mut_list);
        return ret;
    } else {
        return state->nil;
    }
}
lisp_Value* lisp_Value_call(lisp_State* state, lisp_Value* object, lisp_Value* symbol, lisp_Value* args, lisp_Scope* scope) {
    lisp_Map* prototype = lisp_Value_find_prototype(state, object, symbol);
    lisp_Value* value = lisp_Map_get(state, prototype, symbol);

    if (value->type == state->type_function) {
        return lisp_Function_call(state, (lisp_Function*) value->value, args, scope);
    } else if (value->type == state->type_macro) {
        return lisp_Macro_call(state, (lisp_Macro*) value->value, args, scope);
    } else {
        return state->nil;
    }
}


#endif
