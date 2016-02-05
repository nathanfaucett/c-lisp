#ifndef __LISP_GC_C__
#define __LISP_GC_C__


static lisp_GC* lisp_GC_new(void) {
    lisp_GC* gc = (lisp_GC*) malloc(sizeof(lisp_GC));
    gc->root = NULL;
    gc->static_root = NULL;
    gc->size = 0;
    gc->bytes = 0;
    return gc;
}
static void lisp_GC_delete(lisp_GC* gc) {
    if (gc->static_root != NULL) {
        lisp_GCNode_delete(gc->static_root);
    }
    if (gc->root != NULL) {
        lisp_GCNode_delete(gc->root);
    }
    free(gc);
}

static lisp_GCNode* lisp_GC_static_alloc(lisp_GC* gc, lisp_size bytes) {
    lisp_GCNode* gc_node = lisp_GCNode_new(gc->static_root, bytes);
    gc->static_root = gc_node;
    gc->size += 1;
    gc->bytes += bytes;
    return gc_node;
}
static lisp_GCNode* lisp_GC_alloc(lisp_GC* gc, lisp_size bytes) {
    lisp_GCNode* gc_node = lisp_GCNode_new(gc->root, bytes);
    gc->root = gc_node;
    gc->size += 1;
    gc->bytes += bytes;
    return gc_node;
}
static void lisp_GC_dealloc(lisp_GC* gc, void* object) {
    lisp_GCNode* gc_node = gc->root;
    lisp_GCNode* prev = NULL;

    while (gc_node != NULL && gc_node->object != object) {
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
        gc->bytes -= gc_node->bytes;

        gc_node->next = NULL;
        lisp_GCNode_delete(gc_node);
    }
}


#endif
