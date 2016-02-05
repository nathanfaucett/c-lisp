#ifndef __LISP_GC_NODE_C__
#define __LISP_GC_NODE_C__


static lisp_GCNode* lisp_GCNode_new(lisp_GCNode* next, lisp_size bytes) {
    lisp_GCNode* gc_node = (lisp_GCNode*) malloc(sizeof(lisp_GCNode));
    lisp_GCNodeData* root = lisp_GCNodeData_new(NULL, bytes);
    gc_node->marked = LISP_FALSE;
    gc_node->bytes = bytes;
    gc_node->object = root->object;
    gc_node->next = next;
    gc_node->root = root;
    return gc_node;
}
static void lisp_GCNode_delete(lisp_GCNode* gc_node) {
    lisp_GCNodeData_delete(gc_node->root);
    if (gc_node->next != NULL) {
        lisp_GCNode_delete(gc_node->next);
    }
    free(gc_node);
}

static void* lisp_GCNode_assoc(lisp_GC* gc, lisp_GCNode* gc_node, lisp_size bytes) {
    lisp_GCNodeData* new_gc_node_data = lisp_GCNodeData_new(gc_node->root, bytes);
    gc->bytes += bytes;
    gc_node->bytes += bytes;
    return new_gc_node_data->object;
}
static void lisp_GCNode_dissoc(lisp_GC* gc, lisp_GCNode* gc_node, void* object) {
    if (object != gc_node->object) {
        lisp_GCNodeData* gc_node_data = gc_node->root;
        lisp_GCNodeData* prev_gc_node_data = NULL;

        while (gc_node_data != NULL && gc_node_data->object != object) {
            prev_gc_node_data = gc_node_data;
            gc_node_data = gc_node_data->next;
        }

        if (gc_node_data != NULL) {
            if (prev_gc_node_data != NULL) {
                prev_gc_node_data->next = gc_node_data->next;
                gc_node->root = prev_gc_node_data;
            } else {
                gc_node->root = gc_node_data->next;
            }

            gc->bytes -= gc_node_data->bytes;
            gc_node->bytes -= gc_node_data->bytes;

            gc_node_data->next = NULL;
            lisp_GCNodeData_delete(gc_node_data);
        }
    }
}


#endif
