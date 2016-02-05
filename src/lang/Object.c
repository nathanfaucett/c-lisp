#ifndef __LISP_LANG_OBJECT_C__
#define __LISP_LANG_OBJECT_C__


static lisp_Object* lisp_Object_alloc(lisp_State* state, lisp_Object* Type) {
    lisp_GCNode* gc_node = lisp_State_alloc(state, sizeof(lisp_Object));
    lisp_Object* object = (lisp_Object*) gc_node->object;
    lisp_MutableList* Type_values = Type->values;

    object->gc_node = gc_node;
    object->type = Type;

    lisp_Object* size_object = lisp_MutableList_get(state, Type_values, LISP_IDX_TYPE_SIZE);
    lisp_size size = LISP_GET_DATA(size_object, lisp_size);

    if (size != 0) {
        object->data = lisp_State_assoc(state, gc_node, size);
    } else {
        object->data = NULL;
    }

    lisp_MutableList* attributes = (lisp_MutableList*) lisp_MutableList_get(state, Type_values, LISP_IDX_TYPE_ATTRIBUTES)->data;
    if (attributes->size != 0) {
        lisp_MutableList* values = (lisp_MutableList*) lisp_State_assoc(state, gc_node, sizeof(lisp_MutableList));
        values->gc_node = gc_node;
        values->root = NULL;
        values->tail = NULL;
        values->size = 0;
        lisp_MutableList_set_size(state, values, attributes->size);
        object->values = values;
    } else {
        object->values = NULL;
    }

    lisp_Type* type = (lisp_Type*) Type->data;
    if (type->alloc != NULL) {
        type->alloc(state, object);
    }

    return object;
}
static void lisp_Object_mark(lisp_Object* object) {
    lisp_GCNode* gc_node = object->gc_node;

    if (gc_node->marked == LISP_FALSE) {
        gc_node->marked = LISP_TRUE;

        lisp_Object_mark(object->type);

        if (object->values != NULL && object->values->root != NULL) {
            lisp_MutableListNode_mark(object->values->root);
        }

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
        lisp_Object* super = lisp_MutableList_get(state, a->values, LISP_IDX_TYPE_SUPER);

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
