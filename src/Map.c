#ifndef __LISP_MAP_C__
#define __LISP_MAP_C__


static lisp_Map* lisp_Map_constructor(lisp_Map* map) {
    map->keys = lisp_Array_new();
    map->values = lisp_Array_new();
    return map;
}

static void lisp_Map_destructor(lisp_Map* map) {
    lisp_Array_delete(map->keys);
    lisp_Array_delete(map->values);
}

static lisp_Map* lisp_Map_new(void) {
    return lisp_Map_constructor((lisp_Map*) malloc(sizeof(lisp_Map)));
}

static void lisp_Map_delete(lisp_Map* map) {
    lisp_Map_destructor(map);
    free(map);
}

static lisp_u32 lisp_Map_size(lisp_Map* map) {
    return lisp_Array_size(map->keys);
}

static lisp_bool lisp_Map_has(lisp_Map* map, lisp_Value* key) {
    return lisp_Array_index_of(map->keys, key) != -1;
}

static lisp_Value* lisp_Map_get(lisp_Map* map, lisp_Value* key) {
    lisp_i32 index = lisp_Array_index_of(map->keys, key);

    if (index != -1) {
        return lisp_Array_get(map->values, (lisp_u32) index);
    } else {
        return NULL;
    }
}

static void lisp_Map_set(lisp_Map* map, lisp_Value* key, lisp_Value* value) {
    lisp_i32 index = lisp_Array_index_of(map->keys, key);

    if (index != -1) {
        lisp_Array_set(map->keys, index, key);
        lisp_Array_set(map->values, index, value);
    } else {
        lisp_Array_push(map->keys, key);
        lisp_Array_push(map->values, value);
    }
}

static void lisp_Map_remove(lisp_Map* map, lisp_Value* key) {
    lisp_i32 index = lisp_Array_index_of(map->keys, key);

    if (index != -1) {
        lisp_Array_remove(map->keys, index);
        lisp_Array_remove(map->values, index);
    }
}


#endif
