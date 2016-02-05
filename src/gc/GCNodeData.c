#ifndef __LISP_GC_NODE_DATA_C__
#define __LISP_GC_NODE_DATA_C__


static lisp_GCNodeData* lisp_GCNodeData_new(lisp_GCNodeData* next, lisp_size bytes) {
    lisp_GCNodeData* gc_node_data = (lisp_GCNodeData*) malloc(sizeof(lisp_GCNodeData));
    gc_node_data->next = next;
    gc_node_data->bytes = bytes;
    gc_node_data->object = malloc(bytes);
    return gc_node_data;
}
static void lisp_GCNodeData_delete(lisp_GCNodeData* gc_node_data) {
    if (gc_node_data->next != NULL) {
        lisp_GCNodeData_delete(gc_node_data->next);
    }
    free(gc_node_data->object);
    free(gc_node_data);
}


#endif
