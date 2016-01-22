#ifndef __LISP_LANG_LIST_C__
#define __LISP_LANG_LIST_C__


static lisp_ListNode* lisp_ListNode_constructor(lisp_ListNode* node, lisp_ListNode* next, lisp_Value* value) {
    node->ref_count = 1;
    node->next = next;
    node->value = value;
    return node;
}
static void lisp_ListNode_destructor(lisp_State* state, lisp_ListNode* node) {
    if (node->next != NULL) {
        lisp_ListNode_delete(state, node->next);
    }
    lisp_Value_deref(state, node->value);
}

static lisp_ListNode* lisp_ListNode_new(lisp_ListNode* next, lisp_Value* value) {
    return lisp_ListNode_constructor((lisp_ListNode*) malloc(sizeof(lisp_ListNode)), next, value);
}
static void lisp_ListNode_delete(lisp_State* state, lisp_ListNode* node) {
    lisp_ListNode_destructor(state, node);
    free(node);
}

static lisp_ListNode* lisp_ListNode_find_node(lisp_ListNode* node, lisp_u32 index) {
    lisp_u32 i = 0;

    while (node != NULL && i != index) {
        node = node->next;
        i += 1;
    }

    return node;
}

static void lisp_ListNode_ref(lisp_ListNode* node) {
    node->ref_count += 1;
}
static void lisp_ListNode_deref(lisp_State* state, lisp_ListNode* node) {
    node->ref_count -= 1;

    if (node->ref_count == 0) {
        lisp_ListNode_delete(state, node);
    }
}


static void lisp_List_alloc(lisp_State* state, lisp_Value* value) {
    lisp_List* list = (lisp_List*) lisp_State_alloc(state, sizeof(lisp_List));
    value->value = list;
    list->root = NULL;
    list->tail = NULL;
    list->size = 0;
}
static void lisp_List_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_List* list = (lisp_List*) value->value;

    if (list->root != NULL) {
        lisp_ListNode_deref(state, list->root);
    }
    lisp_State_dealloc(state, value->value);
}

static lisp_List* lisp_List_constructor(lisp_List* list, lisp_ListNode* root, lisp_ListNode* tail, lisp_u64 size) {
    list->root = root;
    list->tail = tail;
    list->size = size;
    return list;
}

static lisp_ListNode* lisp_List_find_node(lisp_List* list, lisp_u64 index) {
    if (index == 0) {
        return list->root;
    } else if (index == list->size - 1) {
        return list->tail;
    } else {
        return lisp_ListNode_find_node(list->root, index);
    }
}

static lisp_Value* lisp_List_get(lisp_State* state, lisp_List* list, lisp_u64 index) {
    lisp_ListNode* node = lisp_List_find_node(list, index);

    if (node != NULL) {
        return node->value;
    } else {
        return lisp_Value_new(state, state->type_nil);
    }
}

static lisp_ListNode* lisp_ListNode_push(lisp_ListNode* node, lisp_ListNode* last) {
    if (node == NULL) {
        return last;
    } else {
        return lisp_ListNode_new(
            lisp_ListNode_push(node->next, last),
            node->value
        );
    }
}

static lisp_Value* lisp_List_push(lisp_State* state, lisp_List* list, lisp_Value* value) {
    lisp_Value* new_value = lisp_Value_new(state, state->type_list);
    lisp_ListNode* node = lisp_ListNode_new(NULL, value);

    lisp_Value_ref(value);

    if (list->root != NULL) {
        lisp_List_constructor((lisp_List*) new_value->value, lisp_ListNode_push(list->root, node), node, list->size + 1);
    } else {
        lisp_List_constructor((lisp_List*) new_value->value, node, node, 1);
    }

    return new_value;
}

static lisp_Value* lisp_List_unshift(lisp_State* state, lisp_List* list, lisp_Value* value) {
    lisp_Value* new_value = lisp_Value_new(state, state->type_list);
    lisp_ListNode* node = (lisp_ListNode*) malloc(sizeof(lisp_ListNode));

    lisp_Value_ref(value);

    if (list->root != NULL) {
        lisp_ListNode_constructor(node, list->root, value);
        lisp_ListNode_ref(list->root);
        lisp_List_constructor((lisp_List*) new_value->value, node, list->tail, list->size + 1);
    } else {
        lisp_ListNode_constructor(node, NULL, value);
        lisp_List_constructor((lisp_List*) new_value->value, node, node, 1);
    }

    return new_value;
}

static lisp_Value* lisp_List_pop(lisp_State* state, lisp_List* list) {
    if (list->size == 0) {
        return lisp_Value_ref(state->empty_list);
    } else if (list->size == 1) {
        return lisp_Value_ref(state->empty_list);
    } else {
        lisp_Value* new_value = lisp_Value_new(state, state->type_list);

        lisp_ListNode* root = list->root;
        lisp_ListNode* tail = list->tail;

        lisp_ListNode* new_root = lisp_ListNode_new(NULL, root->value);
        lisp_ListNode* new_tail = new_root;

        while (root != NULL && root != tail) {
            root = root->next;

            new_tail = lisp_ListNode_new(NULL, root->value);
            new_tail->next = new_tail;
        }

        lisp_List_constructor((lisp_List*) new_value->value, new_root, new_tail, list->size - 1);

        return new_value;
    }
}

static lisp_Value* lisp_List_shift(lisp_State* state, lisp_List* list) {
    if (list->size == 0) {
        return lisp_Value_ref(state->empty_list);
    } else if (list->size == 1) {
        return lisp_Value_ref(state->empty_list);
    } else {
        lisp_Value* new_value = lisp_Value_new(state, state->type_list);
        lisp_List_constructor((lisp_List*) new_value->value, list->root->next, list->tail, list->size - 1);
        return new_value;
    }
}

static struct lisp_Value* lisp_List_after(lisp_State* state, lisp_List* list, lisp_u64 index) {
    lisp_ListNode* node = lisp_List_find_node(list, index);

    if (node != NULL) {
        lisp_Value* new_value = lisp_Value_new(state, state->type_list);
        lisp_ListNode_ref(node);
        lisp_List_constructor((lisp_List*) new_value->value, node, list->tail, list->size);
        return new_value;
    } else {
        return lisp_Value_ref(state->empty_list);
    }
}

static lisp_ListNode* lisp_List_copy_from_to(lisp_ListNode* from, lisp_ListNode* to, lisp_ListNode* new_node) {
    if (from != to) {
        return lisp_ListNode_new(lisp_List_copy_from_to(from->next, to, new_node), from->value);
    } else {
        return new_node;
    }
}

static lisp_Value* lisp_List_remove(lisp_State* state, lisp_List* list, lisp_u64 index) {
    if (index == 0) {
        return lisp_List_shift(state, list);
    } else if (index == list->size - 1) {
        return lisp_List_pop(state, list);
    } else {
        lisp_Value* new_value = lisp_Value_new(state, state->type_list);

        lisp_ListNode* removed_node = lisp_ListNode_find_node(list->root, index);
        lisp_ListNode* new_root = lisp_List_copy_from_to(list->root, removed_node, removed_node->next);
        lisp_List_constructor((lisp_List*) new_value->value, new_root, list->tail, list->size - 1);

        return new_value;
    }
}

static lisp_Value* lisp_List_bootstrap(lisp_State* state) {
    lisp_Value* value = lisp_Value_new(state, state->type);
    lisp_Type_constructor(
        (lisp_Type*) value->value,
        NULL, NULL, NULL, NULL,
        state->type_any,
        lisp_List_alloc,
        lisp_List_dealloc
    );
    return value;
}


#endif
