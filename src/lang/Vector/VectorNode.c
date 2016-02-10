#ifndef __LISP_LANG_VECTOR_NODE_C__
#define __LISP_LANG_VECTOR_NODE_C__


static void lisp_VectorNode_alloc(lisp_State* state, lisp_Object* object) {
    lisp_VectorNode* node = (lisp_VectorNode*) object->data;
    lisp_Object** array = (lisp_Object**) lisp_State_assoc(state, object->gc_node, LISP_VECTOR_SIZE * sizeof(lisp_Object*));
    lisp_usize i = 0, il = LISP_VECTOR_SIZE;
    for (; i < il; i++) {
        array[i] = NULL;
    }
    node->array = array;
}
static void lisp_VectorNode_mark(lisp_Object* object) {
    lisp_VectorNode* node = (lisp_VectorNode*) object->data;
    lisp_usize i = 0, il = LISP_VECTOR_SIZE;
    lisp_Object* node_object = node->array[i];
    while (node_object != NULL && i < il) {
        lisp_Object_mark(node_object);
        i += 1;
        node_object = node->array[i];
    }
}

static lisp_Object* lisp_VectorNode_new(lisp_State* state) {
    lisp_Object* object = lisp_Object_boot_size(state, state->VectorNode, sizeof(lisp_VectorNode));
    lisp_VectorNode_alloc(state, object);
    return object;
}

static lisp_Object* lisp_VectorNode_clone(lisp_State* state, lisp_Object* node_object, lisp_usize length) {
    lisp_Object* new_node_object = lisp_VectorNode_new(state);
    lisp_VectorNode* new_node = (lisp_VectorNode*) new_node_object->data;
    lisp_VectorNode* node = (lisp_VectorNode*) node_object->data;

    lisp_usize i = 0, il = length;
    for (; i < il; i++) {
        new_node->array[i] = node->array[i];
    }

    return new_node_object;
}


#endif
