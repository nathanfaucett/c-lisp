#ifndef __LISP_LANG_MUTABLE_LIST_C__
#define __LISP_LANG_MUTABLE_LIST_C__


static void lisp_MutableList_alloc(lisp_State* state, lisp_Object* object) {
    lisp_MutableList_init((lisp_MutableList*) object->data, object->gc_node);
}
static void lisp_MutableList_mark(lisp_Object* object) {
    lisp_MutableList* list = (lisp_MutableList*) object->data;

    if (list->root != NULL) {
        lisp_MutableListNode_mark(list->root);
    }
}

static void lisp_MutableList_init(lisp_MutableList* list, lisp_GCNode* gc_node) {
    list->gc_node = gc_node;
    list->root = NULL;
    list->tail = NULL;
    list->size = 0;
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

static lisp_Object* lisp_MutableList_get(lisp_State* state, lisp_MutableList* list, lisp_size index) {
    lisp_MutableListNode* node = lisp_MutableList_find_node(list, index);

    if (node != NULL) {
        return node->object;
    } else {
        return state->nil;
    }
}
static void lisp_MutableList_set(lisp_MutableList* list, lisp_size index, lisp_Object* object) {
    lisp_MutableListNode* node = lisp_MutableList_find_node(list, index);

    if (node != NULL) {
        node->object = object;
    }
}

static void lisp_MutableList_set_size(lisp_State* state, lisp_MutableList* list, lisp_size new_size) {
    if (new_size == 0) {
        if (list->root != NULL) {
            lisp_MutableListNode_dealloc(state, list->gc_node, list->root);
        }
        list->root = NULL;
        list->tail = NULL;
    } else if (new_size < list->size) {
        lisp_MutableListNode* node = lisp_MutableList_find_node(list, new_size - 1);

        if (node->next != NULL) {
            lisp_MutableListNode_dealloc(state, list->gc_node, node->next);
        }
    } else if (new_size > list->size) {
        lisp_MutableListNode* tail = list->tail;
        lisp_MutableListNode* node = NULL;

        lisp_size i = list->size, il = new_size;
        for (; i < il; i++) {
            node = lisp_MutableListNode_alloc(state, list->gc_node, NULL, state->nil);
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

static void lisp_MutableList_push(lisp_State* state, lisp_MutableList* list, lisp_Object* object) {
    lisp_MutableListNode* node = lisp_MutableListNode_alloc(state, list->gc_node, NULL, object);

    if (list->root != NULL) {
        list->tail->next = node;
        list->tail = node;
    } else {
        list->root = node;
        list->tail = node;
    }

    list->size += 1;
}

static void lisp_MutableList_unshift(lisp_State* state, lisp_MutableList* list, lisp_Object* object) {
    lisp_MutableListNode* node = lisp_MutableListNode_alloc(state, list->gc_node, list->root, object);

    if (list->root != NULL) {
        list->root = node;
    } else {
        list->root = node;
        list->tail = node;
    }

    list->size += 1;
}

static void lisp_MutableList_pop(lisp_State* state, lisp_MutableList* list) {
    if (list->size > 1) {
        lisp_MutableListNode* tail = list->tail;

        list->tail = lisp_MutableList_find_node(list, list->size - 2);
        lisp_MutableListNode_dealloc(state, list->gc_node, tail);

        list->size -= 1;
    } else if (list->size == 1) {
        lisp_MutableListNode_dealloc(state, list->gc_node, list->tail);
        list->root = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

static void lisp_MutableList_shift(lisp_State* state, lisp_MutableList* list) {
    if (list->size > 1) {
        lisp_MutableListNode* root = list->root;

        list->root = root->next;
        lisp_MutableListNode_dealloc(state, list->gc_node, root);

        list->size -= 1;
    } else if (list->size == 1) {
        lisp_MutableListNode_dealloc(state, list->gc_node, list->root);
        list->root = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

static void lisp_MutableList_remove(lisp_State* state, lisp_MutableList* list, lisp_size index) {
    if (index == 0) {
        lisp_MutableList_shift(state, list);
    } else if (index == list->size - 1) {
        lisp_MutableList_pop(state, list);
    } else if (index < list->size) {
        lisp_MutableListNode* node = lisp_MutableList_find_node(list, index - 1);
        lisp_MutableListNode* removed_node = node->next;

        node->next = removed_node->next;
        removed_node->next = NULL;

        lisp_MutableListNode_dealloc(state, list->gc_node, removed_node);

        list->size -= 1;
    }
}


#endif
