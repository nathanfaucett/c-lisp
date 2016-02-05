#ifndef __LISP_LANG_MUTABLE_MAP_C__
#define __LISP_LANG_MUTABLE_MAP_C__


static void lisp_MutableMap_alloc(lisp_State* state, lisp_Object* object) {
    lisp_MutableMap_init(state, (lisp_MutableMap*) object->data, object->gc_node);
}
static void lisp_MutableMap_mark(lisp_Object* object) {
    lisp_MutableMap* map = (lisp_MutableMap*) object->data;

    if (map->entries->root != NULL) {
        lisp_MutableListNode_mark(map->entries->root);
    }
}

static void lisp_MutableMap_init(lisp_State* state, lisp_MutableMap* map, lisp_GCNode* gc_node) {
    lisp_MutableList* entries = (lisp_MutableList*) lisp_State_assoc(state, gc_node, sizeof(lisp_MutableList));
    lisp_MutableList_init(entries, gc_node);
    map->entries = entries;
}

static lisp_size lisp_MutableMap_size(lisp_MutableMap* map) {
    return map->entries->size / 2;
}

static lisp_size lisp_MutableMap_index_of(lisp_State* state, lisp_MutableMap* map, lisp_Object* key) {
    lisp_MutableListNode* node = map->entries->root;
    lisp_size i = 1;

    while (node != NULL) {
        if (lisp_Object_equal(state, key, node->object)) {
            return i;
        } else {
            i += 2;
            node = node->next;
            if (node != NULL) {
                node = node->next;
            } else {
                break;
            }
        }
    }

    return 0;
}

static lisp_bool lisp_MutableMap_has(lisp_State* state, lisp_MutableMap* map, lisp_Object* key) {
    return lisp_MutableMap_index_of(state, map, key) != 0;
}
static lisp_Object* lisp_MutableMap_get(lisp_State* state, lisp_MutableMap* map, lisp_Object* key) {
    lisp_size index = lisp_MutableMap_index_of(state, map, key);

    if (index != 0) {
        return lisp_MutableList_get(state, map->entries, index);
    } else {
        return state->nil;
    }
}

static void lisp_MutableMap_set(lisp_State* state, lisp_MutableMap* map, lisp_Object* key, lisp_Object* object) {
    lisp_size index = lisp_MutableMap_index_of(state, map, key);

    if (index != 0) {
        lisp_MutableList_set(map->entries, index - 1, key);
        lisp_MutableList_set(map->entries, index, object);
    } else {
        lisp_MutableList_push(state, map->entries, key);
        lisp_MutableList_push(state, map->entries, object);
    }
}
static void lisp_MutableMap_remove(lisp_State* state, lisp_MutableMap* map, lisp_Object* key) {
    lisp_size index = lisp_MutableMap_index_of(state, map, key);

    if (index != 0) {
        lisp_MutableList_remove(state, map->entries, index - 1);
        lisp_MutableList_remove(state, map->entries, index);
    }
}


#endif
