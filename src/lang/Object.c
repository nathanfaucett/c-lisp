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
    lisp_size size = LISP_GET_DATA(size_object, lisp_size);

    if (size != 0) {
        object->data = lisp_State_assoc(state, gc_node, size);
    } else {
        object->data = NULL;
    }

    lisp_List* attributes = (lisp_List*) lisp_List_get(state, type_values, LISP_IDX_TYPE_ATTRIBUTES)->data;
    if (attributes->size != 0) {
        object->values = lisp_boot_new_list(state);
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

static lisp_Object* lisp_Object_call1(lisp_State* state, lisp_Object* object, lisp_Object* key, lisp_Object* a0, lisp_Object* scope) {
    return object;
}

static lisp_bool lisp_Object_equal(lisp_State* state, lisp_Object* a, lisp_Object* b) {
    return a == b;
}


#endif
