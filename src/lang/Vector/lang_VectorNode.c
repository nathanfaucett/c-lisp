#ifndef __LISP_LANG_VECTOR_NODE_C__
#define __LISP_LANG_VECTOR_NODE_C__


static void lisp_VectorNode_mark(lisp_VectorNode* node) {
    if (lisp_GCHeader_mark(node->gc_header)) {
        uintsize i = 0, il = LISP_VECTOR_SIZE;

        if (node->nodes != NULL) {
            lisp_VectorNode* subnode = node->nodes[i];
            while (subnode != NULL && i < il) {
                lisp_VectorNode_mark(subnode);
                i += 1;
                subnode = node->nodes[i];
            }
        } else {
            lisp_Object* value = node->values[i];
            while (node != NULL && i < il) {
                lisp_Object_mark(value);
                i += 1;
                value = node->values[i];
            }
        }
    }
}

static lisp_VectorNode* lisp_VectorNode_new_nodes(lisp_State* state) {
    lisp_GCHeader* gc_header = lisp_State_alloc(state, sizeof(lisp_VectorNode));
    lisp_VectorNode* node = (lisp_VectorNode*) gc_header->data;
    node->gc_header = gc_header;
    lisp_VectorNode** nodes = (lisp_VectorNode**) lisp_State_assoc(state, gc_header, LISP_VECTOR_SIZE * sizeof(lisp_VectorNode*));
    uintsize i = 0, il = LISP_VECTOR_SIZE;
    for (; i < il; i++) {
        nodes[i] = NULL;
    }
    node->nodes = nodes;
    node->values = NULL;
    return node;
}
static lisp_VectorNode* lisp_VectorNode_new_values(lisp_State* state) {
    lisp_GCHeader* gc_header = lisp_State_alloc(state, sizeof(lisp_VectorNode));
    lisp_VectorNode* node = (lisp_VectorNode*) gc_header->data;
    node->gc_header = gc_header;
    lisp_Object** values = (lisp_Object**) lisp_State_assoc(state, gc_header, LISP_VECTOR_SIZE * sizeof(lisp_Object*));
    uintsize i = 0, il = LISP_VECTOR_SIZE;
    for (; i < il; i++) {
        values[i] = NULL;
    }
    node->nodes = NULL;
    node->values = values;
    return node;
}

static lisp_VectorNode* lisp_VectorNode_clone(lisp_State* state, lisp_VectorNode* node, uintsize length) {
    lisp_VectorNode* new_node;
    if (node->nodes != NULL) {
        new_node = lisp_VectorNode_new_nodes(state);
        uintsize i = 0, il = length;
        for (; i < il; i++) {
            new_node->nodes[i] = node->nodes[i];
        }
    } else {
        new_node = lisp_VectorNode_new_values(state);
        uintsize i = 0, il = length;
        for (; i < il; i++) {
            new_node->values[i] = node->values[i];
        }
    }
    return new_node;
}


#endif
