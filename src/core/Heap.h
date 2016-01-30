#ifndef __LISP_CORE_HEAP_H__
#define __LISP_CORE_HEAP_H__


typedef struct lisp_HeapNode {
    struct lisp_HeapNode* next;
    lisp_size size;
    void* value;
} lisp_HeapNode;

static lisp_HeapNode* lisp_HeapNode_new(lisp_HeapNode* next, lisp_size size, void* value);
static void lisp_HeapNode_delete(lisp_HeapNode* node);


typedef struct lisp_Heap {
    lisp_HeapNode* root;
    lisp_size size;
    lisp_size bytes;
} lisp_Heap;


static lisp_Heap* lisp_Heap_new(void);
static void lisp_Heap_delete(lisp_Heap* heap);

static void* lisp_Heap_alloc(lisp_Heap* heap, lisp_size size);
static void lisp_Heap_dealloc(lisp_Heap* heap, void* value);


#endif
