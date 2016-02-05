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

static lisp_size lisp_Map_size(lisp_Map* map) {
    if (map->entries != NULL) {
        return ((lisp_List*) map->entries->data)->size / 2;
    } else {
        return 0;
    }
}

static lisp_size lisp_Map_index_of(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    if (map->entries != NULL) {
        lisp_Object* node_object = ((lisp_List*) map->entries->data)->root;
        lisp_ListNode* node = NULL;
        lisp_size i = 1;

        while (node_object != NULL) {
            node = (lisp_ListNode*) node_object->data;

            if (lisp_Object_equal(state, key, node->object)) {
                return i;
            } else {
                i += 2;
                node_object = node->next;
                if (node_object != NULL) {
                    node_object = ((lisp_ListNode*) node_object->data)->next;
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
        return lisp_List_get(state, (lisp_List*) map->entries->data, index);
    } else {
        return state->nil;
    }
}

static lisp_Object* lisp_Map_set(lisp_State* state, lisp_Map* map, lisp_Object* key, lisp_Object* object) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Object* entries = map->entries;
        entries = lisp_List_set(state, (lisp_List*) entries->data, index, object);

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
        entries = lisp_List_push(state, (lisp_List*) entries->data, key);
        entries = lisp_List_push(state, (lisp_List*) entries->data, object);
        ((lisp_Map*) new_map_object->data)->entries = entries;

        return new_map_object;
    }
}
static lisp_Object* lisp_Map_remove(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Object* entries = map->entries;
        entries = lisp_List_remove(state, (lisp_List*) entries->data, index - 1);
        entries = lisp_List_remove(state, (lisp_List*) entries->data, index);

        if (((lisp_List*) entries->data)->size != 0) {
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
        lisp_List_mut_set((lisp_List*) map->entries->data, index, object);
    } else {
        lisp_Object* entries_object = map->entries;
        if (entries_object == NULL) {
            entries_object = lisp_Object_alloc(state, state->List);
        }
        lisp_List* entries = (lisp_List*) entries_object->data;
        lisp_List_mut_push(state, entries, key);
        lisp_List_mut_push(state, entries, object);
    }
}
static void lisp_Map_mut_remove(lisp_State* state, lisp_Map* map, lisp_Object* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_List* entries = (lisp_List*) map->entries->data;
        lisp_List_mut_remove(entries, index - 1);
        lisp_List_mut_remove(entries, index);
    }
}


#endif
