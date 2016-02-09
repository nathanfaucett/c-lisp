#ifndef __LISP_LANG_MAP_C__
#define __LISP_LANG_MAP_C__


static void lisp_Map_alloc(lisp_State* state, lisp_Object* object) {
    lisp_Map* map = (lisp_Map*) object->data;
    map->self = object;
    map->entries = NULL;
}
static void lisp_Map_mark(lisp_Object* object) {
    lisp_Map* map = (lisp_Map*) object->data;

    if (map->entries != NULL) {
        lisp_Object_mark(map->entries);
    }
}

static lisp_Object* lisp_Map_new(lisp_State* state) {
    lisp_Object* object = lisp_Object_boot_size(state, state->Map, sizeof(lisp_Map));
    lisp_Map_alloc(state, object);
    return object;
}

static lisp_size lisp_Map_size(lisp_Map* map) {
    if (map->entries != NULL) {
        return ((lisp_Vector*) map->entries->data)->size / 2;
    } else {
        return 0;
    }
}

static lisp_size lisp_Map_index_of(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    if (map->entries != NULL) {
        lisp_Object* node_object = ((lisp_Vector*) map->entries->data)->root;
        lisp_VectorNode* node = NULL;
        lisp_size i = 1;

        while (node_object != NULL) {
            node = (lisp_VectorNode*) node_object->data;

            if (lisp_Object_equal(state, key, node->object)) {
                return i;
            } else {
                i += 2;
                node_object = node->next;
                if (node_object != NULL) {
                    node_object = ((lisp_VectorNode*) node_object->data)->next;
                } else {
                    break;
                }
            }
        }
        return 0;
    } else {
        return 0;
    }
}

static lisp_bool lisp_Map_has(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    return lisp_Map_index_of(state, map, key) != 0;
}
static lisp_Object* lisp_Map_get(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        return lisp_Vector_get(state, (lisp_Vector*) map->entries->data, index);
    } else {
        return state->nil;
    }
}

static lisp_Object* lisp_Map_set(lisp_State* state, lisp_Map* map, lisp_Object* key, lisp_Object* object) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Object* entries = map->entries;
        entries = lisp_Vector_set(state, (lisp_Vector*) entries->data, index, object);

        if (entries != map->entries) {
            lisp_Object* new_map_object = lisp_Object_alloc(state, state->Map);
            ((lisp_Map*) new_map_object->data)->entries = entries;
            return new_map_object;
        } else {
            return map->self;
        }
    } else {
        lisp_Object* new_map_object = lisp_Object_alloc(state, state->Map);
        lisp_Object* entries = map->entries;
        if (entries == NULL) {
            entries = state->empty_list;
        }
        entries = lisp_Vector_push(state, (lisp_Vector*) entries->data, key);
        entries = lisp_Vector_push(state, (lisp_Vector*) entries->data, object);
        ((lisp_Map*) new_map_object->data)->entries = entries;

        return new_map_object;
    }
}
static lisp_Object* lisp_Map_remove(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Object* entries = map->entries;
        entries = lisp_Vector_remove(state, (lisp_Vector*) entries->data, index - 1);
        entries = lisp_Vector_remove(state, (lisp_Vector*) entries->data, index);

        if (((lisp_Vector*) entries->data)->size != 0) {
            lisp_Object* new_map_object = lisp_Object_alloc(state, state->Map);
            ((lisp_Map*) new_map_object->data)->entries = entries;
            return new_map_object;
        } else {
            return state->empty_map;
        }
    } else {
        return map->self;
    }
}

static void lisp_Map_mut_set(lisp_State* state, lisp_Map* map, lisp_Object* key, lisp_Object* object) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Vector_mut_set((lisp_Vector*) map->entries->data, index, object);
    } else {
        lisp_Object* entries_object = map->entries;
        if (entries_object == NULL) {
            entries_object = lisp_Object_alloc(state, state->Vector);
        }
        lisp_Vector* entries = (lisp_Vector*) entries_object->data;
        lisp_Vector_mut_push(state, entries, key);
        lisp_Vector_mut_push(state, entries, object);
    }
}
static void lisp_Map_mut_remove(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Vector* entries = (lisp_Vector*) map->entries->data;
        lisp_Vector_mut_remove(entries, index - 1);
        lisp_Vector_mut_remove(entries, index);
    }
}

static lisp_bool lisp_Map_equal(lisp_State* state, lisp_Map* a, lisp_Map* b) {
    if (a == b || a->entries == b->entries) {
        return LISP_TRUE;
    } else if (a->entries != NULL && b->entries != NULL) {
        return lisp_Vector_equal(state, (lisp_Vector*) a->entries->data, (lisp_Vector*) b->entries->data);
    } else {
        return LISP_FALSE;
    }
}

static lisp_Object* lisp_Map_export_has(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Vector* list = (lisp_Vector*) args->data;
    lisp_Object* self = lisp_Vector_get(state, list, 0);
    lisp_Object* key = lisp_Vector_get(state, list, 1);

    if (self->type == state->Map) {
        return lisp_Map_has(state, (lisp_Map*) self->data, key) ? state->true : state->false;
    } else {
        return state->false;
    }
}
static lisp_Object* lisp_Map_export_get(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Vector* list = (lisp_Vector*) args->data;
    lisp_Object* self = lisp_Vector_get(state, list, 0);
    lisp_Object* key = lisp_Vector_get(state, list, 1);

    if (self->type == state->Map) {
        return lisp_Map_get(state, (lisp_Map*) self->data, key);
    } else {
        /* fixme - error */
        return state->nil;
    }
}
static lisp_Object* lisp_Map_export_set(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Vector* list = (lisp_Vector*) args->data;
    lisp_Object* self = lisp_Vector_get(state, list, 0);
    lisp_Object* key = lisp_Vector_get(state, list, 1);
    lisp_Object* value = lisp_Vector_get(state, list, 2);

    if (self->type == state->Map) {
        return lisp_Map_set(state, (lisp_Map*) self->data, key, value);
    } else {
        /* fixme - error */
        return state->nil;
    }
}
static lisp_Object* lisp_Map_export_remove(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Vector* list = (lisp_Vector*) args->data;
    lisp_Object* self = lisp_Vector_get(state, list, 0);
    lisp_Object* key = lisp_Vector_get(state, list, 1);

    if (self->type == state->Map) {
        return lisp_Map_remove(state, (lisp_Map*) self->data, key);
    } else {
        /* fixme - error */
        return state->nil;
    }
}
static lisp_Object* lisp_Map_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Object* self = lisp_Vector_get(state, (lisp_Vector*) args->data, 0);

    if (self->type == state->Map) {
        return lisp_String_from_ascii(state, "{}");
    } else {
        return lisp_Object_to_string(state, self);
    }
}
static lisp_Object* lisp_Map_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Vector* list = (lisp_Vector*) args->data;
    lisp_Object* self = lisp_Vector_get(state, list, 0);
    lisp_Object* other = lisp_Vector_get(state, list, 1);

    if (self->type == state->Map && other->type == state->Map) {
        return lisp_Map_equal(state, (lisp_Map*) self->data, (lisp_Map*) other->data) ? state->true : state->false;
    } else {
        return lisp_Object_equal(state, self, other) ? state->true : state->false;
    }
}

static void lisp_Map_boot(lisp_State* state) {
    lisp_Object* Map = state->Map;
    lisp_Vector* values = (lisp_Vector*) Map->values->data;
    lisp_Map* prototype = (lisp_Map*) lisp_Vector_get(state, values, LISP_IDX_TYPE_PROTOTYPE)->data;

    lisp_Vector_mut_set(values, LISP_IDX_TYPE_NAME, lisp_String_from_ascii(state, "Map"));

    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "has"), lisp_Native_new(state, lisp_Map_export_has));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "get"), lisp_Native_new(state, lisp_Map_export_get));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "set"), lisp_Native_new(state, lisp_Map_export_set));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "remove"), lisp_Native_new(state, lisp_Map_export_remove));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "to-string"), lisp_Native_new(state, lisp_Map_export_to_string));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "equal"), lisp_Native_new(state, lisp_Map_export_equal));
}


#endif
