#ifndef __LISP_LANG_MAP_C__
#define __LISP_LANG_MAP_C__


static lisp_Object* lisp_Map_init(lisp_State* state, lisp_Object* map) {
    lisp_Object** values = (lisp_Object**) map->data;
    values[LISP_IDX_MAP_ENTIRES] = state->nil;
    return map;
}
static lisp_Object* lisp_Map_new_type(lisp_State* state, lisp_Object* type) {
    lisp_Object* object = lisp_boot_object_size(state, type, sizeof(void*));
    return lisp_Map_init(state, object);
}

uintsize lisp_Map_size(lisp_State* state, lisp_Object* map) {
    lisp_Object** values = (lisp_Object**) map->data;

    if (values[LISP_IDX_MAP_ENTIRES] != state->nil) {
        return lisp_Vector_size(values[LISP_IDX_MAP_ENTIRES]) / 2;
    } else {
        return 0;
    }
}

uintsize lisp_Map_index_of(lisp_State* state, lisp_Object* map, lisp_Object* key) {
    lisp_Object** values = (lisp_Object**) map->data;

    if (values[LISP_IDX_MAP_ENTIRES] != state->nil) {
        lisp_Object* entries = (lisp_Object*) values[LISP_IDX_MAP_ENTIRES];
        uintsize i = 0, il = lisp_Vector_size(entries);
        while (i < il) {
            if (lisp_Object_equal(state, key, lisp_Vector_get(state, entries, i))) {
                return i + 1;
            } else {
                i += 2;
            }
        }
        return 0;
    } else {
        return 0;
    }
}

bool lisp_Map_has(lisp_State* state, lisp_Object* map, lisp_Object* key) {
    return lisp_Map_index_of(state, map, key) != 0;
}
lisp_Object* lisp_Map_get(lisp_State* state, lisp_Object* map, lisp_Object* key) {
    uintsize index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        return lisp_Vector_get(state, ((lisp_Object**) map->data)[LISP_IDX_MAP_ENTIRES], index);
    } else {
        return state->nil;
    }
}

lisp_Object* lisp_Map_set(lisp_State* state, lisp_Object* map, lisp_Object* key, lisp_Object* object) {
    lisp_Object** values = (lisp_Object**) map->data;
    uintsize index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Object* entries = values[LISP_IDX_MAP_ENTIRES];
        entries = lisp_Vector_set(state, entries, index, object);

        if (entries != values[LISP_IDX_MAP_ENTIRES]) {
            lisp_Object* new_map = lisp_Map_new_type(state, map->type);
            ((lisp_Object**) new_map->data)[LISP_IDX_MAP_ENTIRES] = entries;
            return new_map;
        } else {
            return map;
        }
    } else {
        lisp_Object* entries = values[LISP_IDX_MAP_ENTIRES];
        if (entries == state->nil) {
            entries = lisp_Vector_new_type(state, state->AnyVector);
        }
        entries = lisp_Vector_push(state, entries, key);
        entries = lisp_Vector_push(state, entries, object);

        lisp_Object* new_map = lisp_Map_new_type(state, map->type);
        ((lisp_Object**) new_map->data)[LISP_IDX_MAP_ENTIRES] = entries;
        return new_map;
    }
}
lisp_Object* lisp_Map_remove(lisp_State* state, lisp_Object* map, lisp_Object* key) {
    uintsize index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Object* entries = ((lisp_Object**) map->data)[LISP_IDX_MAP_ENTIRES];
        entries = lisp_Vector_remove(state, entries, index - 1);
        entries = lisp_Vector_remove(state, entries, index);

        if (lisp_Vector_size(entries) != 0) {
            lisp_Object* new_map = lisp_Map_new_type(state, map->type);
            ((lisp_Object**) new_map->data)[LISP_IDX_MAP_ENTIRES] = entries;
            return new_map;
        } else {
            return lisp_Map_new_type(state, map->type);
        }
    } else {
        return map;
    }
}

static void lisp_Map_mut_set(lisp_State* state, lisp_Object* map, lisp_Object* key, lisp_Object* object) {
    lisp_Object** values = (lisp_Object**) map->data;
    uintsize index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Vector_mut_set(state, values[LISP_IDX_MAP_ENTIRES], index, object);
    } else {
        lisp_Object* entries = values[LISP_IDX_MAP_ENTIRES];
        if (entries == state->nil) {
            entries = lisp_Vector_new_type(state, state->AnyVector);
        }
        lisp_Vector_mut_push(state, entries, key);
        lisp_Vector_mut_push(state, entries, object);
    }
}
static void lisp_Map_mut_remove(lisp_State* state, lisp_Object* map, lisp_Object* key) {
    uintsize index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Object* entries = ((lisp_Object**) map->data)[LISP_IDX_MAP_ENTIRES];
        lisp_Vector_mut_remove(state, entries, index - 1);
        lisp_Vector_mut_remove(state, entries, index);
    }
}


#endif
