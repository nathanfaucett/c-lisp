#ifndef __LISP_LANG_OBJECT_C__
#define __LISP_LANG_OBJECT_C__


static lisp_Object* lisp_Object_alloc(lisp_State* state, lisp_Object* type) {
    lisp_GCNode* gc_node = lisp_State_alloc(state, sizeof(lisp_Object));
    lisp_Object* object = (lisp_Object*) gc_node->object;
    lisp_Object* type_values_object = type->values;
    lisp_List* type_values = (lisp_List*) type_values_object->data;

    object->gc_node = gc_node;
    object->type = type;

    lisp_Object* size_object = lisp_List_get(state, type_values, LISP_IDX_TYPE_SIZE);
    lisp_usize size = LISP_GET_DATA(size_object, lisp_usize);

    if (size != 0) {
        object->data = lisp_State_assoc(state, gc_node, size);
    } else {
        object->data = NULL;
    }

    lisp_List* attributes = (lisp_List*) lisp_List_get(state, type_values, LISP_IDX_TYPE_ATTRIBUTES)->data;
    if (attributes->size != 0) {
        object->values = NULL;
    } else {
        object->values = state->empty_list;
    }

    lisp_Type* type_data = (lisp_Type*) type->data;
    if (type_data->alloc != NULL) {
        type_data->alloc(state, object);
    }

    return object;
}
static void lisp_Object_mark(lisp_Object* object) {
    lisp_GCNode* gc_node = object->gc_node;

    if (gc_node->marked == LISP_FALSE) {
        gc_node->marked = LISP_TRUE;

        lisp_Object_mark(object->type);
        lisp_Object_mark(object->values);

        lisp_Type* type = (lisp_Type*) object->type->data;
        if (type->mark != NULL) {
            type->mark(object);
        }
    }
}

static lisp_Object* lisp_Object_boot_alloc(lisp_State* state, lisp_Object* type) {
    lisp_GCNode* gc_node = lisp_State_alloc(state, sizeof(lisp_Object));
    lisp_Object* object = (lisp_Object*) gc_node->object;
    lisp_Object_boot_init(object, gc_node, type);
    return object;
}
static lisp_Object* lisp_Object_boot_init(lisp_Object* object, lisp_GCNode* gc_node, lisp_Object* type) {
    object->gc_node = gc_node;
    object->data = NULL;
    object->type = type;
    object->values = NULL;
    return object;
}
static lisp_Object* lisp_Object_boot_size(lisp_State* state, lisp_Object* type, lisp_usize size) {
    lisp_Object* object = lisp_Object_boot_alloc(state, type);
    object->data = lisp_State_assoc(state, object->gc_node, size);
    return object;
}

static lisp_bool lisp_Object_inherits(lisp_State* state, lisp_Object* a, lisp_Object* b) {
    if (a == b) {
        return LISP_TRUE;
    } else {
        lisp_Object* super = lisp_List_get(state, (lisp_List*) a->values->data, LISP_IDX_TYPE_SUPER);

        if (super != state->nil) {
            return lisp_Object_inherits(state, super, b);
        } else {
            return LISP_FALSE;
        }
    }
}

static lisp_Object* lisp_Object_value_get(lisp_State* state, lisp_Object* object, lisp_Object* key) {
    lisp_Object* type = object->type;
    lisp_List* attributes = (lisp_List*) lisp_List_get(state, (lisp_List*) type->values->data, LISP_IDX_TYPE_ATTRIBUTES)->data;
    lisp_usize index = lisp_List_index_of(state, attributes, key);

    if (index != 0) {
        return lisp_List_get(state, (lisp_List*) object->values->data, index);
    } else {
        return state->nil;
    }
}
static lisp_Object* lisp_Object_value_set(lisp_State* state, lisp_Object* object, lisp_Object* key, lisp_Object* value) {
    lisp_Object* type = object->type;
    lisp_List* attributes = (lisp_List*) lisp_List_get(state, (lisp_List*) type->values->data, LISP_IDX_TYPE_ATTRIBUTES)->data;
    lisp_usize index = lisp_List_index_of(state, attributes, key);

    if (index != 0) {
        lisp_Object* new_values = lisp_List_set(state, (lisp_List*) object->values->data, index, value);

        if (new_values != object->values) {
            lisp_Object* new_object = lisp_Object_alloc(state, type);
            new_object->values = new_values;
            return new_object;
        } else {
            return object;
        }
    } else {
        return object;
    }
}
static lisp_Object* lisp_Object_func_get(lisp_State* state, lisp_Object* type, lisp_Object* key) {
    lisp_List* type_values = (lisp_List*) type->values->data;
    lisp_Map* prototype = (lisp_Map*) lisp_List_get(state, type_values, LISP_IDX_TYPE_PROTOTYPE)->data;

    if (lisp_Map_has(state, prototype, key)) {
        return lisp_Map_get(state, prototype, key);
    } else  {
        lisp_Object* super = lisp_List_get(state, type_values, LISP_IDX_TYPE_SUPER);

        if (super != state->nil) {
            return lisp_Object_func_get(state, super, key);
        } else {
            return state->nil;
        }
    }
}

static lisp_Object* lisp_Object_call1(lisp_State* state, lisp_Object* object, lisp_Object* key, lisp_Object* a0, lisp_Object* scope) {
    lisp_Object* fn = lisp_Object_func_get(state, object->type, key);
    lisp_Object* args = lisp_List_new(state);
    lisp_List* args_list = (lisp_List*) args->data;
    lisp_List_mut_push(state, args_list, object);
    lisp_List_mut_push(state, args_list, a0);
    return lisp_function_call(state, fn, args, scope);
}

static lisp_Object* lisp_Object_to_string(lisp_State* state, lisp_Object* object) {
    return lisp_String_from_ascii(state, "ObjectToString");
}
static lisp_bool lisp_Object_equal(lisp_State* state, lisp_Object* a, lisp_Object* b) {
    return a == b;
}


#endif
