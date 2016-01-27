#ifndef __LISP_UTILS_MUT_MAP_C__
#define __LISP_UTILS_MUT_MAP_C__


static lisp_MutMap* lisp_MutMap_constructor(lisp_MutMap* map) {
    map->entries = lisp_MutList_new();
    return map;
}

static void lisp_MutMap_destructor(lisp_MutMap* map) {
    lisp_MutList_delete(map->entries);
}

static lisp_MutMap* lisp_MutMap_new(void) {
    return lisp_MutMap_constructor((lisp_MutMap*) malloc(sizeof(lisp_MutMap)));
}

static void lisp_MutMap_delete(lisp_MutMap* map) {
    lisp_MutMap_destructor(map);
    free(map);
}

static lisp_u64 lisp_MutMap_size(lisp_MutMap* map) {
    return map->entries->size / 2;
}

static lisp_u64 lisp_MutMap_index_of(lisp_MutMap* map, void* key) {
    for (lisp_u64 i = 0, il = map->entries->size; i < il; i += 2) {
        if (key == lisp_MutList_get(map->entries, i)) {
            return i + 1;
        }
    }
    return 0;
}

static lisp_bool lisp_MutMap_has(lisp_MutMap* map, void* key) {
    return lisp_MutMap_index_of(map, key) != 0;
}

static void* lisp_MutMap_get(lisp_MutMap* map, void* key) {
    lisp_u64 index = lisp_MutMap_index_of(map, key);

    if (index != 0) {
        return lisp_MutList_get(map->entries, index - 1);
    } else {
        return NULL;
    }
}

static void lisp_MutMap_set(lisp_MutMap* map, void* key, void* value) {
    lisp_u64 index = lisp_MutMap_index_of(map, key);

    if (index != 0) {
        lisp_MutList_set(map->entries, index - 1, key);
        lisp_MutList_set(map->entries, index, value);
    } else {
        lisp_MutList_push(map->entries, key);
        lisp_MutList_push(map->entries, value);
    }
}

static void lisp_MutMap_remove(lisp_MutMap* map, void* key) {
    lisp_u64 index = lisp_MutMap_index_of(map, key);

    if (index != 0) {
        lisp_MutList_remove(map->entries, index - 1);
        lisp_MutList_remove(map->entries, index);
    }
}


#endif
