#ifndef __LISP_STATE_MEMORY_C__
#define __LISP_STATE_MEMORY_C__


static inline lisp_MemoryNode* lisp_MemoryNode_constructor(
    lisp_MemoryNode* node, lisp_MemoryNode* next, lisp_Value* value
) {
    node->next = next;
    node->value = value;
    return node;
}

static inline void lisp_MemoryNode_destructor(lisp_MemoryNode* node) {
    if (node->next != NULL) {
        lisp_MemoryNode_destructor(node->next);
    }

    free(node->value);
    free(node);
}


static inline lisp_Memory* lisp_Memory_constructor(lisp_Memory* memory) {
    memory->root = NULL;
    memory->tail = NULL;
    memory->size = 0;
    return memory;
}

static inline void lisp_Memory_destructor(lisp_Memory* memory) {
    if (memory->root != NULL) {
        lisp_MemoryNode_destructor(memory->root);
    }
}

static inline lisp_Memory* lisp_Memory_new(void) {
    return lisp_Memory_constructor((lisp_Memory*) malloc(sizeof(lisp_Memory)));
}
static inline void lisp_Memory_delete(lisp_Memory* memory) {
    lisp_Memory_destructor(memory);
    free(memory);
}

static inline lisp_Value* lisp_Memory_alloc(lisp_Memory* memory) {
    lisp_MemoryNode* node = (lisp_MemoryNode*) malloc(sizeof(lisp_MemoryNode));
    lisp_Value* value = (lisp_Value*) malloc(sizeof(lisp_Value));

    if (memory->root != NULL) {
        lisp_MemoryNode_constructor(node, memory->root, value);
        memory->root = node;
    } else {
        lisp_MemoryNode_constructor(node, NULL, value);
        memory->root = node;
        memory->tail = node;
    }

    memory->size += 1;

    return value;
}

static inline void lisp_Memory_dealloc(lisp_Memory* memory, lisp_Value* value) {
    lisp_MemoryNode* node = memory->root;
    lisp_MemoryNode* prev = NULL;

    while (node != NULL && node->value != value) {
        prev = node;
        node = node->next;
    }

    if (node != NULL) {
        lisp_MemoryNode* next = node->next;
        node->next = NULL;

        if (prev != NULL) {
            prev->next = next;
        }
        lisp_MemoryNode_destructor(node);

        memory->root = next;
        memory->size -= 1;
    }
}


#endif
