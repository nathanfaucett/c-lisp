#ifndef __LISP_LANG_MAP_C__
#define __LISP_LANG_MAP_C__


static void lisp_Map_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Map* map = (lisp_Map*) value->data;
    map->entries = NULL;
    map->self = value;
}
static void lisp_Map_mark(lisp_Value* value) {
    lisp_Map* map = (lisp_Map*) value->data;

    if (map->entries != NULL) {
        lisp_Value_mark(map->entries);
    }
}

static lisp_size lisp_Map_size(lisp_Map* map) {
    if (map->entries != NULL) {
        return ((lisp_List*) map->entries->data)->size / 2;
    } else {
        return 0;
    }
}

static lisp_size lisp_Map_index_of(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    if (map->entries != NULL) {
        lisp_Value* node_value = ((lisp_List*) map->entries->data)->root;
        lisp_ListNode* node = NULL;
        lisp_size i = 1;

        while (node_value != NULL) {
            node = (lisp_ListNode*) node_value->data;

            if (lisp_Value_equal(state, key, node->value)) {
                return i;
            } else {
                i += 2;
                node_value = node->next;
                if (node_value != NULL) {
                    node_value = ((lisp_ListNode*) node_value->data)->next;
                }
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
        return lisp_List_get(state, (lisp_List*) map->entries->data, index);
    } else {
        return state->nil;
    }
}
static lisp_Value* lisp_Map_set(lisp_State* state, lisp_Map* map, lisp_Value* key, lisp_Value* value) {
    lisp_Value* new_map_value = lisp_Value_alloc(state, state->Map);
    lisp_Value* entries;

    lisp_size index = lisp_Map_index_of(state, map, key);

    if (map->entries != NULL) {
        entries = map->entries;
    } else {
        entries = lisp_Value_alloc(state, state->List);
    }

    if (index != 0) {
        entries = lisp_List_set(state, (lisp_List*) entries->data, index - 1, key);
        entries = lisp_List_set(state, (lisp_List*) entries->data, index, value);
    } else {
        entries = lisp_List_push(state, (lisp_List*) entries->data, key);
        entries = lisp_List_push(state, (lisp_List*) entries->data, value);
    }

    ((lisp_Map*) new_map_value->data)->entries = entries;

    return new_map_value;
}
static lisp_Value* lisp_Map_remove(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Value* new_map_value = lisp_Value_alloc(state, state->Map);

        lisp_Value* entries = map->entries;
        entries = lisp_List_remove(state, (lisp_List*) entries->data, index - 1);
        entries = lisp_List_remove(state, (lisp_List*) entries->data, index);

        ((lisp_Map*) new_map_value->data)->entries = entries;

        return new_map_value;
    } else {
        return map->self;
    }
}

static lisp_bool lisp_Map_equal(lisp_State* state, lisp_Map* a, lisp_Map* b) {
    if (a == b) {
        return LISP_TRUE;
    } else if (a->entries != NULL && a->entries != NULL) {
        return lisp_List_equal(state, (lisp_List*) a->entries->data, (lisp_List*) b->entries->data);
    } else {
        return LISP_FALSE;
    }
}


#endif
