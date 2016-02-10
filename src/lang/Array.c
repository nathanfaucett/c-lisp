#ifndef __LISP_LANG_ARRAY_C__
#define __LISP_LANG_ARRAY_C__


static void lisp_Array_alloc(lisp_State* state, lisp_Object* object) {
    lisp_Array* array = (lisp_Array*) object->data;
    array->self = object;
    array->objects = NULL;
    array->size = 0;
}
static void lisp_Array_mark(lisp_Object* object) {
    lisp_Array* array = (lisp_Array*) object->data;

    if (array->objects != NULL) {
        lisp_Object* object = NULL;
        lisp_size i = 0, il = array->size;
        for (; i < il; i++) {
            object = array->objects[i];
            if (object != NULL) {
                lisp_Object_mark(array->objects[i]);
            }
        }
    }
}

static lisp_Object* lisp_Array_new(lisp_State* state) {
    lisp_Object* object = lisp_Object_boot_size(state, state->Array, sizeof(lisp_Array));
    lisp_Array_alloc(state, object);
    return object;
}

static void lisp_Array_set_size(lisp_State* state, lisp_Array* array, lisp_size size) {
    if (size > 0) {
        if (array->objects != NULL) {
            lisp_State_dissoc(state, array->self->gc_node, array->objects);
        }
        lisp_Object** objects = lisp_State_assoc(state, array->self->gc_node, size * sizeof(lisp_Object*));
        lisp_size i = 0, il = size;
        for (; i < il; i++) {
            objects[i] = NULL;
        }

        array->objects = objects;
        array->size = size;
    }
}
static lisp_Object* lisp_Array_get(lisp_State* state, lisp_Array* array, lisp_size index) {
    if (index < array->size) {
        lisp_Object* object = array->objects[index];

        if (object != NULL) {
            return object;
        } else {
            return state->nil;
        }
    } else {
        return state->nil;
    }
}
static void lisp_Array_set(lisp_Array* array, lisp_size index, lisp_Object* value) {
    if (index < array->size) {
        array->objects[index] = value;
    }
}

static lisp_bool lisp_Array_equal(lisp_State* state, lisp_Array* a, lisp_Array* b) {
    if (a == b) {
        return LISP_TRUE;
    } else if (a->size == b->size) {
        lisp_size i = 0, il = a->size;
        for (; i < il; i++) {
            if (!lisp_Object_equal(state, lisp_Array_get(state, a, i), lisp_Array_get(state, b, i))) {
                return LISP_FALSE;
            }
        }
        return LISP_TRUE;
    } else {
        return LISP_FALSE;
    }
}


#endif
