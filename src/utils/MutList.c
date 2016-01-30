#ifndef __LISP_UTILS_MUT_LIST_C__
#define __LISP_UTILS_MUT_LIST_C__


static lisp_MutListNode* lisp_lisp_MutListNode_constructor(
    lisp_MutListNode* node, lisp_MutListNode* next, void* value
) {
    node->next = next;
    node->value = value;
    return node;
}

static void lisp_MutListNode_destructor(lisp_MutListNode* node) {
    if (node->next != NULL) {
        lisp_MutListNode_delete(node->next);
    }
}

static lisp_MutListNode* lisp_MutListNode_new(lisp_MutListNode* next, void* value) {
    return lisp_lisp_MutListNode_constructor(
        (lisp_MutListNode*) malloc(sizeof(lisp_MutListNode)), next, value
    );
}

static void lisp_MutListNode_delete(lisp_MutListNode* node) {
    lisp_MutListNode_destructor(node);
    free(node);
}

static lisp_MutListNode* lisp_MutListNode_find_node(lisp_MutListNode* node, lisp_size index) {
    lisp_size i = 0;

    while (node != NULL && i != index) {
        node = node->next;
        i += 1;
    }

    return node;
}


static lisp_MutList* lisp_MutList_constructor(lisp_MutList* mut_list) {
    mut_list->root = NULL;
    mut_list->tail = NULL;
    mut_list->size = 0;
    return mut_list;
}

static void lisp_MutList_destructor(lisp_MutList* mut_list) {
    if (mut_list->root != NULL) {
        lisp_MutListNode_delete(mut_list->root);
    }
}

static lisp_MutList* lisp_MutList_new(void) {
    return lisp_MutList_constructor((lisp_MutList*) malloc(sizeof(lisp_MutList)));
}

static void lisp_MutList_delete(lisp_MutList* mut_list) {
    lisp_MutList_destructor(mut_list);
    free(mut_list);
}

static lisp_MutListNode* lisp_MutList_find_node(lisp_MutList* mut_list, lisp_size index) {
    if (index == 0) {
        return mut_list->root;
    } else if (index == mut_list->size - 1) {
        return mut_list->tail;
    } else if (index < mut_list->size) {
        return lisp_MutListNode_find_node(mut_list->root, index);
    } else {
        return NULL;
    }
}

static lisp_size lisp_MutList_index_of(lisp_MutList* mut_list, void* value) {
    lisp_MutListNode* node = mut_list->root;
    lisp_size index = 0;

    while (node != NULL) {
        if (node->value == value) {
            return index + 1;
        }
        node = node->next;
        index += 1;
    }

    return 0;
}

static void* lisp_MutList_get(lisp_MutList* mut_list, lisp_size index) {
    lisp_MutListNode* node = lisp_MutList_find_node(mut_list, index);

    if (node != NULL) {
        return node->value;
    } else {
        return NULL;
    }
}

static void lisp_MutList_set(lisp_MutList* mut_list, lisp_size index, void* value) {
    lisp_MutListNode* node = lisp_MutList_find_node(mut_list, index);

    if (node != NULL) {
        node->value = value;
    }
}

static void lisp_MutList_push(lisp_MutList* mut_list, void* value) {
    lisp_MutListNode* node = lisp_MutListNode_new(NULL, value);

    if (mut_list->root != NULL) {
        mut_list->tail->next = node;
        mut_list->tail = node;
    } else {
        mut_list->root = node;
        mut_list->tail = node;
    }

    mut_list->size += 1;
}

static void lisp_MutList_unshift(lisp_MutList* mut_list, void* value) {
    lisp_MutListNode* node = lisp_MutListNode_new(mut_list->root, value);

    if (mut_list->root != NULL) {
        mut_list->root = node;
    } else {
        mut_list->root = node;
        mut_list->tail = node;
    }

    mut_list->size += 1;
}

static void* lisp_MutList_pop(lisp_MutList* mut_list) {
    void* value = NULL;

    if (mut_list->size > 1) {
        lisp_MutListNode* tail = mut_list->tail;
        value = tail->value;

        mut_list->tail = lisp_MutList_find_node(mut_list, mut_list->size - 2);
        lisp_MutListNode_delete(tail);

        mut_list->size -= 1;
    } else if (mut_list->size == 1) {
        value = mut_list->tail->value;
        lisp_MutListNode_delete(mut_list->tail);

        mut_list->root = NULL;
        mut_list->tail = NULL;
        mut_list->size = 0;
    }

    return value;
}

static void* lisp_MutList_shift(lisp_MutList* mut_list) {
    void* value = NULL;

    if (mut_list->size > 1) {
        lisp_MutListNode* root = mut_list->root;
        value = root->value;

        mut_list->root = root->next;
        lisp_MutListNode_delete(root);

        mut_list->size -= 1;
    } else if (mut_list->size == 1) {
        value = mut_list->root->value;
        lisp_MutListNode_delete(mut_list->root);

        mut_list->root = NULL;
        mut_list->tail = NULL;
        mut_list->size = 0;
    }

    return value;
}

static void lisp_MutList_remove(lisp_MutList* mut_list, lisp_size index) {
    if (index == 0) {
        lisp_MutList_shift(mut_list);
    } else if (index == mut_list->size - 1) {
        lisp_MutList_pop(mut_list);
    } else if (index < mut_list->size) {
        lisp_MutListNode* node = lisp_MutList_find_node(mut_list, index - 1);
        lisp_MutListNode* removed_node = node->next;

        node->next = removed_node->next;
        removed_node->next = NULL;

        lisp_MutListNode_delete(removed_node);

        mut_list->size -= 1;
    }
}


#endif
