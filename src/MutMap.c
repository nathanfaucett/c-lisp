#ifndef __LISP_MAP_C__
#define __LISP_MAP_C__


static lisp_MutMap* lisp_MutMap_constructor(lisp_MutMap* map) {
    map->keys = lisp_MutList_new();
    map->values = lisp_MutList_new();
    return map;
}

static void lisp_MutMap_destructor(lisp_MutMap* map) {
    lisp_MutList_delete(map->keys);
    lisp_MutList_delete(map->values);
}

static lisp_MutMap* lisp_MutMap_new(void) {
    return lisp_MutMap_constructor((lisp_MutMap*) malloc(sizeof(lisp_MutMap)));
}

static void lisp_MutMap_delete(lisp_MutMap* map) {
    lisp_MutMap_destructor(map);
    free(map);
}

static lisp_u32 lisp_MutMap_size(lisp_MutMap* map) {
    return lisp_MutList_size(map->keys);
}

static lisp_bool lisp_MutMap_has(lisp_MutMap* map, lisp_Value* key) {
    return lisp_MutList_index_of(map->keys, key) != -1;
}

static lisp_Value* lisp_MutMap_get(lisp_MutMap* map, lisp_Value* key) {
    lisp_i32 index = lisp_MutList_index_of(map->keys, key);

    if (index != -1) {
        return lisp_MutList_get(map->values, (lisp_u32) index);
    } else {
        return NULL;
    }
}

static void lisp_MutMap_set(lisp_MutMap* map, lisp_Value* key, lisp_Value* value) {
    lisp_i32 index = lisp_MutList_index_of(map->keys, key);

    if (index != -1) {
        lisp_MutList_set(map->keys, index, key);
        lisp_MutList_set(map->values, index, value);
    } else {
        lisp_MutList_push(map->keys, key);
        lisp_MutList_push(map->values, value);
    }
}

static void lisp_MutMap_remove(lisp_MutMap* map, lisp_Value* key) {
    lisp_i32 index = lisp_MutList_index_of(map->keys, key);

    if (index != -1) {
        lisp_MutList_remove(map->keys, index);
        lisp_MutList_remove(map->values, index);
    }
}


#endif
