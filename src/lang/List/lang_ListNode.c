#ifndef __LISP_LANG_LIST_NODE_C__
#define __LISP_LANG_LIST_NODE_C__



static lisp_Object* lisp_ListNode_new(lisp_State* state, lisp_Object* next, lisp_Object* value) {
    lisp_Object* object = lisp_boot_object_size(state, state->ListNode, sizeof(void*) * 2);
    lisp_Object** values = (lisp_Object**) object->data;
    values[LISP_IDX_LIST_NODE_NEXT] = next;
    values[LISP_IDX_LIST_NODE_VALUE] = value;
    return object;
}

static lisp_Object* lisp_ListNode_find_node(lisp_Object* node, uintsize index) {
    lisp_Object** values = NULL;
    uintsize i = 0;

    while (node != NULL && i != index) {
        values = (lisp_Object**) node->data;
        node = values[LISP_IDX_LIST_NODE_NEXT];
        i += 1;
    }

    return node;
}
static lisp_Object* lisp_ListNode_copy_from_to(lisp_State* state, lisp_Object* from, lisp_Object* to, lisp_Object* new_node) {
    if (from != to) {
        lisp_Object** values = (lisp_Object**) from->data;

        return lisp_ListNode_new(
            state,
            lisp_ListNode_copy_from_to(state, values[LISP_IDX_LIST_NODE_NEXT], to, new_node),
            values[LISP_IDX_LIST_NODE_VALUE]
        );
    } else {
        return new_node;
    }
}
static lisp_Object* lisp_ListNode_push(lisp_State* state, lisp_Object* node, lisp_Object* last_node) {
    if (node != NULL) {
        lisp_Object** values = (lisp_Object**) node->data;

        return lisp_ListNode_new(
            state,
            lisp_ListNode_push(state, values[LISP_IDX_LIST_NODE_NEXT], last_node),
            values[LISP_IDX_LIST_NODE_VALUE]
        );
    } else {
        return last_node;
    }
}


#endif
