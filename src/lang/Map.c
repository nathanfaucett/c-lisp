#ifndef __LISP_LANG_MAP_C__
#define __LISP_LANG_MAP_C__


static void lisp_Map_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Map* map = (lisp_Map*) value->data;
    lisp_Array* entries = (lisp_Array*) lisp_State_alloc(state, sizeof(lisp_Array));
    entries->root = NULL;
    entries->tail = NULL;
    entries->size = 0;
    map->entries = entries;
}
static void lisp_Map_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Map* map = (lisp_Map*) value->data;

    if (map->entries->root != NULL) {
        lisp_ArrayNode_dealloc(map->entries->root);
    }
    lisp_State_dealloc(state, map->entries);
}
static void lisp_Map_mark(lisp_Value* value) {
    lisp_Map* map = (lisp_Map*) value->data;

    if (map->entries->root != NULL) {
        lisp_ArrayNode_mark(map->entries->root);
    }
}

static lisp_size lisp_Map_size(lisp_Map* map) {
    return map->entries->size / 2;
}

static lisp_size lisp_Map_index_of(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    lisp_ArrayNode* node = map->entries->root;
    lisp_size i = 1;

    while (node != NULL) {
        if (lisp_Value_equal(state, key, node->value)) {
            return i;
        } else {
            i += 2;
            node = node->next;
            if (node != NULL) {
                node = node->next;
            }
        }
    }

    return 0;
}

static lisp_bool lisp_Map_has(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    return lisp_Map_index_of(state, map, key) != 0;
}
static lisp_Value* lisp_Map_get(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        return lisp_Array_get(state, map->entries, index);
    } else {
        return state->nil;
    }
}
static void lisp_Map_set(lisp_State* state, lisp_Map* map, lisp_Value* key, lisp_Value* value) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Array_set(map->entries, index - 1, key);
        lisp_Array_set(map->entries, index, value);
    } else {
        lisp_Array_push(map->entries, key);
        lisp_Array_push(map->entries, value);
    }
}
static void lisp_Map_remove(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Array_remove(map->entries, index - 1);
        lisp_Array_remove(map->entries, index);
    }
}

static lisp_bool lisp_Map_equal(lisp_State* state, lisp_Map* a, lisp_Map* b) {
    if (a == b) {
        return LISP_TRUE;
    } else {
        return lisp_Array_equal(state, a->entries, b->entries);
    }
}


#endif
