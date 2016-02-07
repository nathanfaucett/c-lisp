#ifndef __LISP_LANG_LIST_NODE_C__
#define __LISP_LANG_LIST_NODE_C__


static void lisp_ListNode_alloc(lisp_State* state, lisp_Object* object) {
    lisp_ListNode* node = (lisp_ListNode*) object->data;
    node->next = NULL;
    node->object = NULL;
}
static void lisp_ListNode_mark(lisp_Object* object) {
    lisp_ListNode* node = (lisp_ListNode*) object->data;

    if (node->next != NULL) {
        lisp_ListNode_mark(node->next);
    }
    lisp_Object_mark(node->object);
}

static lisp_Object* lisp_ListNode_new(lisp_State* state) {
    lisp_Object* object = lisp_Object_boot_size(state, state->ListNode, sizeof(lisp_ListNode));
    lisp_ListNode_alloc(state, object);
    return object;
}

static lisp_Object* lisp_ListNode_find_node(lisp_Object* node, lisp_size index) {
    lisp_size i = 0;

    while (node != NULL && i != index) {
        node = ((lisp_ListNode*) node->data)->next;
        i += 1;
    }

    return node;
}
static lisp_Object* lisp_ListNode_copy_from_to(lisp_State* state, lisp_Object* from, lisp_Object* to, lisp_Object* new_node) {
    if (from != to) {
        lisp_ListNode* from_node = (lisp_ListNode*) from->data;

        lisp_Object* node_object = lisp_Object_alloc(state, state->ListNode);
        lisp_ListNode* node = (lisp_ListNode*) node_object->data;

        node->next = lisp_ListNode_copy_from_to(state, from_node->next, to, new_node);
        node->object = from_node->object;

        return node_object;
    } else {
        return new_node;
    }
}
static lisp_Object* lisp_ListNode_push(lisp_State* state, lisp_Object* node_object, lisp_Object* last_node_object) {
    if (node_object != NULL) {
        lisp_ListNode* node = (lisp_ListNode*) node_object->data;

        lisp_Object* new_node_object = lisp_Object_alloc(state, state->ListNode);
        lisp_ListNode* new_node = (lisp_ListNode*) new_node_object->data;

        new_node->next = lisp_ListNode_push(state, node->next, last_node_object);
        new_node->object = node->object;

        return new_node_object;
    } else {
        return last_node_object;
    }
}


#endif
