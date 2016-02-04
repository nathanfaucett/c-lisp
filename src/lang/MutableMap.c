#ifndef __LISP_LANG_MUTABLE_MAP_C__
#define __LISP_LANG_MUTABLE_MAP_C__


static void lisp_MutableMap_alloc(lisp_State* state, lisp_Value* value) {
    lisp_MutableMap* map = (lisp_MutableMap*) value->data;
    lisp_MutableList* entries = (lisp_MutableList*) lisp_State_alloc(state, sizeof(lisp_MutableList));
    entries->root = NULL;
    entries->tail = NULL;
    entries->size = 0;
    map->entries = entries;
}
static void lisp_MutableMap_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_MutableMap* map = (lisp_MutableMap*) value->data;

    if (map->entries->root != NULL) {
        lisp_MutableListNode_dealloc(map->entries->root);
    }
    lisp_State_dealloc(state, map->entries);
}
static void lisp_MutableMap_mark(lisp_Value* value) {
    lisp_MutableMap* map = (lisp_MutableMap*) value->data;

    if (map->entries->root != NULL) {
        lisp_MutableListNode_mark(map->entries->root);
    }
}

static lisp_size lisp_MutableMap_size(lisp_MutableMap* map) {
    return map->entries->size / 2;
}

static lisp_size lisp_MutableMap_index_of(lisp_State* state, lisp_MutableMap* map, lisp_Value* key) {
    lisp_MutableListNode* node = map->entries->root;
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

static lisp_bool lisp_MutableMap_has(lisp_State* state, lisp_MutableMap* map, lisp_Value* key) {
    return lisp_MutableMap_index_of(state, map, key) != 0;
}
static lisp_Value* lisp_MutableMap_get(lisp_State* state, lisp_MutableMap* map, lisp_Value* key) {
    lisp_size index = lisp_MutableMap_index_of(state, map, key);

    if (index != 0) {
        return lisp_MutableList_get(state, map->entries, index);
    } else {
        return state->nil;
    }
}
static void lisp_MutableMap_set(lisp_State* state, lisp_MutableMap* map, lisp_Value* key, lisp_Value* value) {
    lisp_size index = lisp_MutableMap_index_of(state, map, key);

    if (index != 0) {
        lisp_MutableList_set(map->entries, index - 1, key);
        lisp_MutableList_set(map->entries, index, value);
    } else {
        lisp_MutableList_push(map->entries, key);
        lisp_MutableList_push(map->entries, value);
    }
}
static void lisp_MutableMap_remove(lisp_State* state, lisp_MutableMap* map, lisp_Value* key) {
    lisp_size index = lisp_MutableMap_index_of(state, map, key);

    if (index != 0) {
        lisp_MutableList_remove(map->entries, index - 1);
        lisp_MutableList_remove(map->entries, index);
    }
}

static lisp_bool lisp_MutableMap_equal(lisp_State* state, lisp_MutableMap* a, lisp_MutableMap* b) {
    if (a == b) {
        return LISP_TRUE;
    } else {
        return lisp_MutableList_equal(state, a->entries, b->entries);
    }
}


#endif
