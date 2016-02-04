#ifndef __LISP_LANG_MUTABLE_LIST_C__
#define __LISP_LANG_MUTABLE_LIST_C__


static void lisp_MutableList_alloc(lisp_State* state, lisp_Value* value) {
    lisp_MutableList* list = (lisp_MutableList*) value->data;
    list->root = NULL;
    list->tail = NULL;
    list->size = 0;
}
static void lisp_MutableList_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_MutableList* list = (lisp_MutableList*) value->data;

    if (list->root != NULL) {
        lisp_MutableListNode_dealloc(list->root);
    }
}
static void lisp_MutableList_mark(lisp_Value* value) {
    lisp_MutableList* list = (lisp_MutableList*) value->data;

    if (list->root != NULL) {
        lisp_MutableListNode_mark(list->root);
    }
}

static lisp_MutableListNode* lisp_MutableList_find_node(lisp_MutableList* list, lisp_size index) {
    if (index == 0) {
        return list->root;
    } else if (index == list->size - 1) {
        return list->tail;
    } else if (index < list->size) {
        return lisp_MutableListNode_find_node(list->root, index);
    } else {
        return NULL;
    }
}

static lisp_size lisp_MutableList_index_of(lisp_State* state, lisp_MutableList* list, lisp_Value* key) {
    lisp_MutableListNode* node = list->root;
    lisp_size index = 1;

    while (node != NULL) {
        if (lisp_Value_equal(state, node->value, key)) {
            return index;
        }
        index += 1;
        node = node->next;
    }

    return 0;
}

static lisp_Value* lisp_MutableList_get(lisp_State* state, lisp_MutableList* list, lisp_size index) {
    lisp_MutableListNode* node = lisp_MutableList_find_node(list, index);

    if (node != NULL) {
        return node->value;
    } else {
        return state->nil;
    }
}
static void lisp_MutableList_set(lisp_MutableList* list, lisp_size index, lisp_Value* value) {
    lisp_MutableListNode* node = lisp_MutableList_find_node(list, index);

    if (node != NULL) {
        node->value = value;
    }
}

static void lisp_MutableList_set_size(lisp_State* state, lisp_MutableList* list, lisp_size new_size) {
    if (new_size == 0) {
        if (list->root != NULL) {
            lisp_MutableListNode_dealloc(list->root);
        }
        list->root = NULL;
        list->tail = NULL;
    } else if (new_size < list->size) {
        lisp_MutableListNode* node = lisp_MutableList_find_node(list, new_size - 1);

        if (node->next != NULL) {
            lisp_MutableListNode_dealloc(node->next);
        }
    } else if (new_size > list->size) {
        lisp_MutableListNode* tail = list->tail;
        lisp_MutableListNode* node = NULL;

        lisp_size i = list->size, il = new_size;
        for (; i < il; i++) {
            node = lisp_MutableListNode_alloc(NULL, state->nil);
            if (tail != NULL) {
                tail->next = node;
            } else {
                list->root = node;
            }
            tail = node;
        }

        list->tail = tail;
    }
    list->size = new_size;
}

static void lisp_MutableList_push(lisp_MutableList* list, lisp_Value* value) {
    lisp_MutableListNode* node = lisp_MutableListNode_alloc(NULL, value);

    if (list->root != NULL) {
        list->tail->next = node;
        list->tail = node;
    } else {
        list->root = node;
        list->tail = node;
    }

    list->size += 1;
}

static void lisp_MutableList_unshift(lisp_MutableList* list, lisp_Value* value) {
    lisp_MutableListNode* node = lisp_MutableListNode_alloc(list->root, value);

    if (list->root != NULL) {
        list->root = node;
    } else {
        list->root = node;
        list->tail = node;
    }

    list->size += 1;
}

static void lisp_MutableList_pop(lisp_MutableList* list) {
    if (list->size > 1) {
        lisp_MutableListNode* tail = list->tail;

        list->tail = lisp_MutableList_find_node(list, list->size - 2);
        lisp_MutableListNode_dealloc(tail);

        list->size -= 1;
    } else if (list->size == 1) {
        lisp_MutableListNode_dealloc(list->tail);
        list->root = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

static void lisp_MutableList_shift(lisp_MutableList* list) {
    if (list->size > 1) {
        lisp_MutableListNode* root = list->root;

        list->root = root->next;
        lisp_MutableListNode_dealloc(root);

        list->size -= 1;
    } else if (list->size == 1) {
        lisp_MutableListNode_dealloc(list->root);
        list->root = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

static void lisp_MutableList_remove(lisp_MutableList* list, lisp_size index) {
    if (index == 0) {
        lisp_MutableList_shift(list);
    } else if (index == list->size - 1) {
        lisp_MutableList_pop(list);
    } else if (index < list->size) {
        lisp_MutableListNode* node = lisp_MutableList_find_node(list, index - 1);
        lisp_MutableListNode* removed_node = node->next;

        node->next = removed_node->next;
        removed_node->next = NULL;

        lisp_MutableListNode_dealloc(removed_node);

        list->size -= 1;
    }
}

static lisp_bool lisp_MutableList_equal(lisp_State* state, lisp_MutableList* a, lisp_MutableList* b) {
    if (a == b) {
        return LISP_TRUE;
    } else if (a->size != b->size) {
        return LISP_FALSE;
    } else {
        lisp_MutableListNode* anode = a->root;
        lisp_MutableListNode* bnode = b->root;

        while (anode != NULL) {
            if (lisp_Value_equal(state, anode->value, bnode->value)) {
                anode = anode->next;
                bnode = bnode->next;
            } else {
                return LISP_FALSE;
            }
        }

        return LISP_TRUE;
    }
}


static lisp_Value* lisp_MutableList_export_index_of(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return args;
}

static lisp_Value* lisp_MutableList_export_get(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    lisp_Value* self;
    lisp_Value* index;

    if (args->type == state->MutableList) {
        self = lisp_MutableList_get(state, (lisp_MutableList*) args->data, 0);
        index = lisp_MutableList_get(state, (lisp_MutableList*) args->data, 1);
    } else {
        lisp_Value* get = lisp_Symbol_from_ascii(state, "get");
        self = lisp_Value_call1(state, args, get, lisp_Number_UInt(state, 0), scope);
        index = lisp_Value_call1(state, args, get, lisp_Number_UInt(state, 1), scope);
    }

    return state->false;
}
static lisp_Value* lisp_MutableList_export_set(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return args;
}

static lisp_Value* lisp_MutableList_export_push(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return args;
}
static lisp_Value* lisp_MutableList_export_unshift(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return args;
}

static lisp_Value* lisp_MutableList_export_pop(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return args;
}
static lisp_Value* lisp_MutableList_export_shift(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return args;
}
static lisp_Value* lisp_MutableList_export_remove(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return args;
}

static lisp_Value* lisp_MutableList_export_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return lisp_String_from_ascii(state, "(MutableList)");
}
static lisp_Value* lisp_MutableList_export_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    lisp_Value* get = lisp_Symbol_from_ascii(state, "get");
    lisp_Value* self = lisp_Value_call1(state, args, get, lisp_Number_UInt(state, 0), scope);
    lisp_Value* other = lisp_Value_call1(state, args, get, lisp_Number_UInt(state, 1), scope);

    if (self->type == state->MutableList && other->type == state->MutableList) {
        if (lisp_MutableList_equal(state, (lisp_MutableList*) self->data, (lisp_MutableList*) other->data)) {
            return state->true;
        }
    }

    return state->false;
}

static void lisp_MutableList_boot(lisp_State* state) {
    /*
    lisp_Value* MutableList = state->MutableList;
    lisp_Map* prototype = (lisp_Map*) lisp_MutableList_get(state, (lisp_MutableList*) MutableList->values->data, LISP_IDX_TYPE_PROTOTYPE)->data;
    */
}


#endif
