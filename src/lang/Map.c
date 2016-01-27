#ifndef __LISP_LANG_MAP_C__
#define __LISP_LANG_MAP_C__


static void lisp_Map_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Map* map = (lisp_Map*) lisp_State_alloc(state, sizeof(lisp_Map));
    value->value = map;
    map->value = value;
    map->entries = NULL;
}
static void lisp_Map_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Map* map = (lisp_Map*) value->value;
    if (map->entries != NULL) {
        lisp_Value_deref(state, map->entries);
    }
    lisp_State_dealloc(state, value->value);
}

static lisp_u64 lisp_Map_size(lisp_Map* map) {
    if (map->entries != NULL) {
        return ((lisp_List*) map->entries->value)->size / 2;
    } else {
        return 0;
    }
}

static lisp_Value* lisp_Map_from_mut_list(lisp_State* state, lisp_MutList* mut_list) {
    if (mut_list->size > 0) {
        if (mut_list->size % 2 != 0) {
            lisp_MutList_push(mut_list, lisp_Value_ref(state->nil));
        }

        lisp_Value* map_value = lisp_Value_alloc(state, state->type_map);
        ((lisp_Map*) map_value->value)->entries = lisp_List_from_mut_list(state, mut_list);

        return map_value;
    } else {
        return lisp_Value_alloc(state, state->type_map);
    }
}

static lisp_u64 lisp_Map_index_of(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    if (map->entries != NULL) {
        lisp_List* entries = (lisp_List*) map->entries->value;
        lisp_Value* equal = lisp_Symbol_new_ascii(state, "equal");
        lisp_ListNode* node = entries->root;
        lisp_u64 index = 0;

        while (node != NULL) {
            lisp_Value* value = lisp_Value_call_arg1(state, node->value, equal, key, NULL);

            if (value->type != state->type_bool) {
                lisp_Value_deref(state, value);
                value = lisp_Value_alloc(state, state->type_bool);
                ((lisp_Bool*) value->value)->value = LISP_FALSE;
            }

            lisp_bool bool_value = ((lisp_Bool*) value->value)->value;
            lisp_Value_deref(state, value);

            if (bool_value) {
                index += 2;
                node = node->next;
                if (node != NULL) {
                    node = node->next;
                }
            } else {
                lisp_Value_deref(state, equal);
                return index + 1;;
            }
        }
        return 0;
    } else {
        return 0;
    }
}

static lisp_bool lisp_Map_has(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    return lisp_Map_index_of(state, map, key) != 0;
}

static lisp_Value* lisp_Map_get(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    lisp_u64 index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        return lisp_List_get(state, (lisp_List*) map->entries->value, index - 1);
    } else {
        return lisp_Value_ref(state->nil);
    }
}

static lisp_Value* lisp_Map_set(lisp_State* state, lisp_Map* map, lisp_Value* key, lisp_Value* value) {
    lisp_u64 index = lisp_Map_index_of(state, map, key);

    lisp_Value* tmp;
    lisp_Value* new_entries;

    if (index != 0) {
        tmp = lisp_List_set(state, (lisp_List*) map->entries->value, index - 1, key);
        new_entries = lisp_List_set(state, (lisp_List*) tmp->value, index, value);
    } else {
        if (map->entries == NULL) {
            map->entries = lisp_Value_alloc(state, state->type_list);
        }

        tmp = lisp_List_push(state, (lisp_List*) map->entries->value, key);
        new_entries = lisp_List_push(state, (lisp_List*) tmp->value, value);
    }
    lisp_Value_deref(state, tmp);

    if (new_entries != map->entries) {
        lisp_Value_deref(state, map->entries);

        lisp_Value* new_map = lisp_Value_alloc(state, state->type_map);
        ((lisp_Map*) new_map->value)->entries = new_entries;

        return new_map;
    } else {
        return lisp_Value_ref(map->value);
    }
}

static lisp_Value* lisp_Map_remove(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    lisp_u64 index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Value* tmp = lisp_List_remove(state, (lisp_List*) map->entries->value, index - 1);
        lisp_Value* new_entries = lisp_List_remove(state, (lisp_List*) tmp->value, index);
        lisp_Value_deref(state, tmp);

        if (new_entries != map->entries) {
            lisp_Value_deref(state, map->entries);

            lisp_Value* new_map = lisp_Value_alloc(state, state->type_map);
            ((lisp_Map*) new_map->value)->entries = new_entries;

            return new_map;
        } else {
            return lisp_Value_ref(map->value);
        }
    } else {
        return lisp_Value_ref(map->value);
    }
}


#endif
