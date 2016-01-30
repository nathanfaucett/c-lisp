#ifndef __LISP_LANG_MAP_C__
#define __LISP_LANG_MAP_C__


static void lisp_Map_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Map* map = (lisp_Map*) value->data;
    lisp_Seq* entries = (lisp_Seq*) malloc(sizeof(lisp_Seq));
    entries->root = NULL;
    entries->tail = NULL;
    entries->size = 0;
    map->entries = entries;
}
static void lisp_Map_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Map* map = (lisp_Map*) value->data;

    if (map->entries->root != NULL) {
        lisp_SeqNode_dealloc(map->entries->root);
    }
    free(map->entries);
}
static void lisp_Map_mark(lisp_Value* value) {
    lisp_Map* map = (lisp_Map*) value->data;

    if (map->entries->root != NULL) {
        lisp_SeqNode_mark(map->entries->root);
    }
}

static lisp_size lisp_Map_size(lisp_Map* map) {
    return map->entries->size / 2;
}

static lisp_size lisp_Map_index_of(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    lisp_SeqNode* node = map->entries->root;
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
        return lisp_Seq_get(state, map->entries, index);
    } else {
        return state->nil;
    }
}
static void lisp_Map_set(lisp_State* state, lisp_Map* map, lisp_Value* key, lisp_Value* value) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Seq_set(map->entries, index - 1, key);
        lisp_Seq_set(map->entries, index, value);
    } else {
        lisp_Seq_push(map->entries, key);
        lisp_Seq_push(map->entries, value);
    }
}
static void lisp_Map_remove(lisp_State* state, lisp_Map* map, lisp_Value* key) {
    lisp_size index = lisp_Map_index_of(state, map, key);

    if (index != 0) {
        lisp_Seq_remove(map->entries, index - 1);
        lisp_Seq_remove(map->entries, index);
    }
}

static lisp_bool lisp_Map_equal(lisp_State* state, lisp_Map* a, lisp_Map* b) {
    if (a == b) {
        return LISP_TRUE;
    } else {
        return lisp_Seq_equal(state, a->entries, b->entries);
    }
}


#endif
