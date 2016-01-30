#ifndef __LISP_CORE_HEAP_C__
#define __LISP_CORE_HEAP_C__


static lisp_HeapNode* lisp_HeapNode_new(lisp_HeapNode* next, lisp_size size, void* value) {
    lisp_HeapNode* node = (lisp_HeapNode*) malloc(sizeof(lisp_HeapNode));
    node->next = next;
    node->size = size;
    node->value = value;
    return node;
}
static void lisp_HeapNode_delete(lisp_HeapNode* node) {
    if (node->next != NULL) {
        lisp_HeapNode_delete(node->next);
    }
    free(node->value);
    free(node);
}


static lisp_Heap* lisp_Heap_new(void) {
    lisp_Heap* heap = (lisp_Heap*) malloc(sizeof(lisp_Heap));
    heap->root = NULL;
    heap->size = 0;
    heap->bytes = 0;
    return heap;
}
static void lisp_Heap_delete(lisp_Heap* heap) {
    if (heap->root != NULL) {
        lisp_HeapNode_delete(heap->root);
    }
    free(heap);
}

static void* lisp_Heap_alloc(lisp_Heap* heap, lisp_size size) {
    void* value = malloc(size);
    lisp_HeapNode* node = lisp_HeapNode_new(heap->root, size, value);
    heap->root = node;
    heap->size += 1;
    heap->bytes += size;
    return value;
}
static void lisp_Heap_dealloc(lisp_Heap* heap, void* value) {
    lisp_HeapNode* node = heap->root;
    lisp_HeapNode* prev = NULL;

    while (node != NULL && node->value != value) {
        prev = node;
        node = node->next;
    }

    if (node != NULL) {
        if (prev != NULL) {
            prev->next = node->next;
            heap->root = prev;
        } else {
            heap->root = node->next;
        }
        node->next = NULL;

        heap->size -= 1;
        heap->bytes -= node->size;

        lisp_HeapNode_delete(node);
    }
}


#endif
