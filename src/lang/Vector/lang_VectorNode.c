#ifndef __LISP_LANG_VECTOR_NODE_C__
#define __LISP_LANG_VECTOR_NODE_C__


static lisp_Object* lisp_VectorNode_new(lisp_State* state) {
    lisp_Object* object = lisp_boot_object_size(state, state->VectorNode, sizeof(void*) * LISP_VECTOR_SIZE);
    lisp_Object** values = (lisp_Object**) object->data;
    uintsize i = 0, il = LISP_VECTOR_SIZE;
    while (i < il) {
        values[i] = state->nil;
        i += 1;
    }
    return object;
}

static lisp_Object* lisp_VectorNode_clone(lisp_State* state, lisp_Object* node, uintsize length) {
    lisp_Object** values = (lisp_Object**) node->data;

    lisp_Object* new_node = lisp_VectorNode_new(state);
    lisp_Object** new_node_values = (lisp_Object**) new_node->data;

    uintsize i = 0, il = length;
    for (; i < il; i++) {
        new_node_values[i] = values[i];
    }

    return new_node;
}


#endif
