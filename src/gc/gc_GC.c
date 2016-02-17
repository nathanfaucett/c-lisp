#ifndef __LISP_GC_GC_C__
#define __LISP_GC_GC_C__


static lisp_GC* lisp_GC_new(void) {
    lisp_GC* gc = (lisp_GC*) malloc(sizeof(lisp_GC));
    gc->root = NULL;
    gc->size = 0;
    gc->bytes = 0;
    return gc;
}
static void lisp_GC_delete(lisp_GC* gc) {
    if (gc->root != NULL) {
        lisp_GCNode_delete(gc->root);
    }
    free(gc);
}

static lisp_GCHeader* lisp_GC_alloc(lisp_GC* gc, uintsize bytes) {
    lisp_GCHeader* gc_header = lisp_GCHeader_new(bytes);
    lisp_GCNode* gc_node = lisp_GCNode_new(gc->root, gc_header);
    gc->root = gc_node;
    gc->size += 1;
    gc->bytes += bytes;
    return gc_header;
}
static void lisp_GC_dealloc(lisp_GC* gc, lisp_GCHeader* gc_header) {
    lisp_GCNode* gc_node = gc->root;
    lisp_GCNode* prev = NULL;

    while (gc_node != NULL && gc_node->gc_header != gc_header) {
        prev = gc_node;
        gc_node = gc_node->next;
    }

    if (gc_node != NULL) {
        if (prev != NULL) {
            prev->next = gc_node->next;
            gc->root = prev;
        } else {
            gc->root = gc_node->next;
        }

        gc->size -= 1;
        gc->bytes -= gc_header->bytes;

        gc_node->next = NULL;
        lisp_GCNode_delete(gc_node);
    }
}


#endif
