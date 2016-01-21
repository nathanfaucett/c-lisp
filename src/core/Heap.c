#ifndef __LISP_CORE_HEAP_C__
#define __LISP_CORE_HEAP_C__


static lisp_HeapNode* lisp_HeapNode_constructor(lisp_HeapNode* node, lisp_HeapNode* next, size_t size, void* value) {
    node->next = next;
    node->size = size;
    node->value = value;
    return node;
}
static void lisp_HeapNode_destructor(lisp_HeapNode* node) {
    if (node->next != NULL) {
        lisp_HeapNode_delete(node->next);
    }
    free(node->value);
}

static lisp_HeapNode* lisp_HeapNode_new(lisp_HeapNode* next, size_t size, void* value) {
    return lisp_HeapNode_constructor((lisp_HeapNode*) malloc(sizeof(lisp_HeapNode)), next, size, value);
}
static void lisp_HeapNode_delete(lisp_HeapNode* node) {
    lisp_HeapNode_destructor(node);
    free(node);
}


static lisp_Heap* lisp_Heap_constructor(lisp_Heap* node) {
    node->root = NULL;
    node->size = 0;
    node->bytes = 0;
    return node;
}
static void lisp_Heap_destructor(lisp_Heap* node) {
    if (node->root != NULL) {
        lisp_HeapNode_delete(node->root);
    }
}

static lisp_Heap* lisp_Heap_new(void) {
    return lisp_Heap_constructor((lisp_Heap*) malloc(sizeof(lisp_Heap)));
}
static void lisp_Heap_delete(lisp_Heap* node) {
    lisp_Heap_destructor(node);
    free(node);
}

static void* lisp_Heap_alloc(lisp_Heap* heap, size_t size) {
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
