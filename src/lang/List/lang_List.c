#ifndef __LISP_LANG_LIST_C__
#define __LISP_LANG_LIST_C__


static void lisp_List_alloc(lisp_State* state, lisp_Object* object) {
    lisp_List* list = (lisp_List*) object->data;
    list->self = object;
    list->root = NULL;
    list->tail = NULL;
    list->size = 0;
}
static void lisp_List_mark(lisp_Object* object) {
    lisp_List* list = (lisp_List*) object->data;

    if (list->root != NULL) {
        lisp_ListNode_mark(list->root);
    }
}

static lisp_Object* lisp_List_new(lisp_State* state, lisp_Object* template) {
    lisp_Object* object = lisp_Object_boot_template_size(state, state->List, template, sizeof(lisp_List));
    lisp_List_alloc(state, object);
    return object;
}
static lisp_Object* lisp_List_new_type(lisp_State* state, lisp_Object* Type) {
    lisp_Object* object = lisp_Object_boot_size(state, Type, sizeof(lisp_List));
    lisp_List_alloc(state, object);
    return object;
}

static lisp_ListNode* lisp_List_find_node(lisp_List* list, uintsize index) {
    if (index == 0) {
        return list->root;
    } else if (index == list->size - 1) {
        return list->tail;
    } else if (index < list->size) {
        return lisp_ListNode_find_node(list->root, index);
    } else {
        return NULL;
    }
}
static uintsize lisp_List_index_of(lisp_State* state, lisp_List* list, lisp_Object* key) {
    lisp_ListNode* node = list->root;
    uintsize index = 1;

    while (node != NULL) {
        if (lisp_Object_equal(state, node->value, key)) {
            return index;
        } else {
            index += 1;
            node = node->next;
        }
    }

    return 0;
}

static lisp_Object* lisp_List_concat(lisp_State* state, lisp_List* a, lisp_List* b) {
    if (a->size == 0) {
        return b->self;
    } else if (b->size == 0) {
        return a->self;
    } else {
        lisp_Object* new_list_object = lisp_List_new_type(state, a->self->type);
        lisp_List* new_list = (lisp_List*) new_list_object->data;

        lisp_ListNode* node = a->root;

        while (node != NULL) {
            lisp_List_mut_push(state, new_list, node->value);
            node = node->next;
        }
        node = b->root;
        while (node != NULL) {
            lisp_List_mut_push(state, new_list, node->value);
            node = node->next;
        }

        return new_list_object;
    }
}

static void lisp_List_mut_set_size(lisp_State* state, lisp_List* list, uintsize size) {
    lisp_ListNode* tail = NULL;
    lisp_ListNode* node = NULL;

    uintsize i = 0, il = size;
    for (; i < il; i++) {
        node = lisp_ListNode_new(state, NULL, state->nil_value);

        if (tail != NULL) {
            tail->next = node;
        } else {
            list->root = node;
        }
        tail = node;
    }

    list->tail = tail;
    list->size = size;
}

static lisp_Object* lisp_List_get(lisp_State* state, lisp_List* list, uintsize index) {
    lisp_ListNode* node = lisp_List_find_node(list, index);

    if (node != NULL) {
        return node->value;
    } else {
        return state->nil_value;
    }
}
static lisp_Object* lisp_List_set(lisp_State* state, lisp_List* list, uintsize index, lisp_Object* value) {
    if (index < list->size) {
        lisp_ListNode* node = lisp_List_find_node(list, index);

        if (lisp_Object_equal(state, node->value, value)) {
            return list->self;
        } else {
            lisp_Object* new_list_object = lisp_List_new_type(state, list->self->type);
            lisp_List* new_list = (lisp_List*) new_list_object->data;

            lisp_ListNode* new_node = lisp_ListNode_new(state, node->next, value);

            new_list->root = lisp_ListNode_copy_from_to(state, list->root, node, new_node);
            new_list->tail = node->next == NULL ? new_node : list->tail;
            new_list->size = list->size;

            return new_list_object;
        }
    } else {
        return list->self;
    }
}
static void lisp_List_mut_set(lisp_List* list, uintsize index, lisp_Object* value) {
    if (index < list->size) {
        lisp_ListNode* node = lisp_List_find_node(list, index);
        node->value = value;
    }
}

static lisp_Object* lisp_List_push(lisp_State* state, lisp_List* list, lisp_Object* value) {
    lisp_Object* new_list_object = lisp_List_new_type(state, list->self->type);
    lisp_List* new_list = (lisp_List*) new_list_object->data;

    lisp_ListNode* node = lisp_ListNode_new(state, NULL, value);

    if (list->root != NULL) {
        new_list->root = lisp_ListNode_push(state, list->root, node);
        new_list->tail = node;
        new_list->size = list->size + 1;
    } else {
        new_list->root = node;
        new_list->tail = node;
        new_list->size = 1;
    }

    return new_list_object;
}
static void lisp_List_mut_push(lisp_State* state, lisp_List* list, lisp_Object* value) {
    lisp_ListNode* node = lisp_ListNode_new(state, NULL, value);

    if (list->root != NULL) {
        list->tail->next = node;
        list->tail = node;
    } else {
        list->root = node;
        list->tail = node;
    }

    list->size += 1;
}

static lisp_Object* lisp_List_unshift(lisp_State* state, lisp_List* list, lisp_Object* value) {
    lisp_Object* new_list_object = lisp_List_new_type(state, list->self->type);
    lisp_List* new_list = (lisp_List*) new_list_object->data;

    lisp_ListNode* node = lisp_ListNode_new(state, list->root, value);

    if (list->root != NULL) {
        new_list->tail = list->tail;
        new_list->size = list->size + 1;
    } else {
        new_list->tail = node;
        new_list->size = 1;
    }

    new_list->root = node;

    return new_list_object;
}

static lisp_Object* lisp_List_pop(lisp_State* state, lisp_List* list) {
    if (list->size > 1) {
        lisp_Object* new_list_object = lisp_List_new_type(state, list->self->type);
        lisp_List* new_list = (lisp_List*) new_list_object->data;

        lisp_ListNode* tail = list->tail;
        lisp_ListNode* root = list->root;

        lisp_ListNode* new_root = lisp_ListNode_new(state, NULL, root->value);
        lisp_ListNode* new_tail = new_root;
        lisp_ListNode* tmp = NULL;

        while (true) {
            root = root->next;

            if (root == NULL || root == tail) {
                break;
            } else {
                tmp = lisp_ListNode_new(state, NULL, root->value);
                new_tail->next = tmp;
                new_tail = tmp;
            }
        }

        new_list->root = new_root;
        new_list->tail = new_tail;
        new_list->size = list->size - 1;

        return new_list_object;
    } else {
        return lisp_List_new_type(state, list->self->type);
    }
}
static lisp_Object* lisp_List_shift(lisp_State* state, lisp_List* list) {
    if (list->size > 1) {
        lisp_Object* new_list_object = lisp_List_new_type(state, list->self->type);
        lisp_List* new_list = (lisp_List*) new_list_object->data;

        new_list->root = list->root->next;
        new_list->tail = list->tail;
        new_list->size = list->size - 1;

        return new_list_object;
    } else {
        return lisp_List_new_type(state, list->self->type);
    }
}
static lisp_Object* lisp_List_remove(lisp_State* state, lisp_List* list, uintsize index) {
    if (index == 0) {
        return lisp_List_shift(state, list);
    } else if (index == list->size - 1) {
        return lisp_List_pop(state, list);
    } else if (index < list->size) {
        lisp_Object* new_list_object = lisp_List_new_type(state, list->self->type);
        lisp_List* new_list = (lisp_List*) new_list_object->data;

        lisp_ListNode* removed_node = lisp_ListNode_find_node(list->root, index);
        lisp_ListNode* new_root = lisp_ListNode_copy_from_to(state, list->root, removed_node, removed_node->next);

        new_list->root = new_root;
        new_list->tail = list->tail;
        new_list->size = list->size - 1;

        return new_list_object;
    } else {
        return list->self;
    }
}

static void lisp_List_mut_pop(lisp_List* list) {
    if (list->size > 1) {
        list->tail = lisp_List_find_node(list, list->size - 2);
        list->size -= 1;
    } else if (list->size == 1) {
        list->root = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}
static void lisp_List_mut_shift(lisp_List* list) {
    if (list->size > 1) {
        list->root = list->root->next;
        list->size -= 1;
    } else if (list->size == 1) {
        list->root = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}
static void lisp_List_mut_remove(lisp_List* list, uintsize index) {
    if (index == 0) {
        lisp_List_mut_shift(list);
    } else if (index == list->size - 1) {
        lisp_List_mut_pop(list);
    } else if (index < list->size) {
        lisp_ListNode* node = lisp_List_find_node(list, index - 1);
        node->next = node->next->next;
        list->size -= 1;
    }
}

static bool lisp_List_equal(lisp_State* state, lisp_List* a, lisp_List* b) {
    if (a == b) {
        return true;
    } else if (a->size != b->size) {
        return false;
    } else {
        lisp_ListNode* anode = a->root;
        lisp_ListNode* bnode = b->root;

        while (anode != NULL) {
            if (lisp_Object_equal(state, anode->value, bnode->value)) {
                anode = anode->next;
                bnode = bnode->next;
            } else {
                return false;
            }
        }

        return true;
    }
}


#endif
