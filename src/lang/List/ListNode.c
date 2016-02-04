#ifndef __LISP_LANG_LIST_NODE_C__
#define __LISP_LANG_LIST_NODE_C__


static void lisp_ListNode_alloc(lisp_State* state, lisp_Value* value) {
    lisp_ListNode* node = (lisp_ListNode*) value->data;
    node->next = NULL;
    node->value = NULL;
}
static void lisp_ListNode_mark(lisp_Value* value) {
    lisp_ListNode* node = (lisp_ListNode*) value->data;

    if (node->next != NULL) {
        lisp_ListNode_mark(node->next);
    }
    lisp_Value_mark(node->value);
}

static lisp_Value* lisp_ListNode_find_node(lisp_Value* node, lisp_size index) {
    lisp_size i = 0;

    while (node != NULL && i != index) {
        node = ((lisp_ListNode*) node->data)->next;
        i += 1;
    }

    return node;
}
static lisp_Value* lisp_ListNode_copy_from_to(lisp_State* state, lisp_Value* from, lisp_Value* to, lisp_Value* new_node) {
    if (from != to) {
        lisp_ListNode* from_node = (lisp_ListNode*) from->data;

        lisp_Value* node_value = lisp_Value_alloc(state, state->ListNode);
        lisp_ListNode* node = (lisp_ListNode*) node_value->data;

        node->next = lisp_ListNode_copy_from_to(state, from_node->next, to, new_node);
        node->value = from_node->value;

        return node_value;
    } else {
        return new_node;
    }
}
static lisp_Value* lisp_ListNode_push(lisp_State* state, lisp_Value* node_value, lisp_Value* last_node_value) {
    if (node_value != NULL) {
        lisp_ListNode* node = (lisp_ListNode*) node_value->data;

        lisp_Value* new_node_value = lisp_Value_alloc(state, state->ListNode);
        lisp_ListNode* new_node = (lisp_ListNode*) new_node_value->data;

        new_node->next = lisp_ListNode_push(state, node->next, last_node_value);
        new_node->value = node->value;

        return new_node_value;
    } else {
        return last_node_value;
    }
}


#endif
