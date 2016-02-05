#ifndef __LISP_LANG_MUTABLE_MAP_C__
#define __LISP_LANG_MUTABLE_MAP_C__


static void lisp_Map_alloc(lisp_State* state, lisp_Object* object) {
    lisp_Map_init(state, (lisp_Map*) object->data, object->gc_node);
}
static void lisp_Map_mark(lisp_Object* object) {
    lisp_Map* map = (lisp_Map*) object->data;

    if (map->entries->root != NULL) {
        lisp_ListNode_mark(map->entries->root);
    }
}

static void lisp_Map_init(lisp_State* state, lisp_Map* map, lisp_GCNode* gc_node) {
    lisp_List* entries = (lisp_List*) lisp_State_assoc(state, gc_node, sizeof(lisp_List));
    lisp_List_init(entries, gc_node);
    map->entries = entries;
}

static lisp_size lisp_Map_size(lisp_Map* map) {
    return map->entries->size / 2;
}

static lisp_size lisp_Map_index_of(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    lisp_ListNode* node = map->entries->root;
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

static lisp_bool lisp_Map_has(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    return lisp_Map_index_of(state, map, key) != 0;
}
static lisp_Object* lisp_Map_get(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        return lisp_List_get(state, map->entries, index);
    } else {
        return state->nil;
    }
}

static void lisp_Map_set(lisp_State* state, lisp_Map* map, lisp_Object* key, lisp_Object* object) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_List_set(map->entries, index, object);
    } else {
        lisp_List_push(state, map->entries, key);
        lisp_List_push(state, map->entries, object);
    }
}
static void lisp_Map_remove(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_List_remove(state, map->entries, index - 1);
        lisp_List_remove(state, map->entries, index);
    }
}


#endif
