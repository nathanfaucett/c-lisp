#ifndef __LISP_GC_GC_HEADER_C__
#define __LISP_GC_GC_HEADER_C__


static lisp_GCHeader* lisp_GCHeader_new(uintsize bytes) {
    lisp_GCHeader* gc_header = (lisp_GCHeader*) malloc(sizeof(lisp_GCHeader));
    lisp_GCData* gc_data = lisp_GCData_new(bytes);
    lisp_GCHeaderNode* gc_header_node = lisp_GCHeaderNode_new(NULL, gc_data);
    gc_header->marked = false;
    gc_header->data = gc_data->data;
    gc_header->bytes = bytes;
    gc_header->root = gc_header_node;
    return gc_header;
}
static void lisp_GCHeader_delete(lisp_GCHeader* gc_header) {
    if (gc_header->root != NULL) {
        lisp_GCHeaderNode_delete(gc_header->root);
    }
    free(gc_header);
}

static void* lisp_GCHeader_assoc(lisp_GC* gc, lisp_GCHeader* gc_header, uintsize bytes) {
    lisp_GCData* gc_data = lisp_GCData_new(bytes);
    gc->bytes += bytes;
    gc_header->bytes += bytes;
    gc_header->root = lisp_GCHeaderNode_new(gc_header->root, gc_data);
    return gc_data->data;
}
static void lisp_GCHeader_dissoc(lisp_GC* gc, lisp_GCHeader* gc_header, void* data) {
    if (data != gc_header->data) {
        lisp_GCHeaderNode* gc_header_node = gc_header->root;
        lisp_GCHeaderNode* prev = NULL;

        while (gc_header_node != NULL && gc_header_node->gc_data->data != data) {
            prev = gc_header_node;
            gc_header_node = gc_header_node->next;
        }

        if (gc_header_node != NULL) {
            if (prev != NULL) {
                prev->next = gc_header_node->next;
                gc_header->root = prev;
            } else {
                gc_header->root = gc_header_node->next;
            }
            gc->bytes -= gc_header->bytes;
            gc_header->bytes -= gc_header->bytes;
            gc_header_node->next = NULL;
            lisp_GCHeaderNode_delete(gc_header_node);
        }
    }
}

bool lisp_GCHeader_mark(lisp_GCHeader* gc_header) {
    if (gc_header->marked) {
        gc_header->marked = true;
        return true;
    } else {
        return false;
    }
}


#endif
