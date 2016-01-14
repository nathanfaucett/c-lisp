#ifndef __LISP_CORE_MEMORY_H__
#define __LISP_CORE_MEMORY_H__


typedef struct lisp_MemoryNode {
    struct lisp_MemoryNode* next;
    struct lisp_Value* value;
} lisp_MemoryNode;

static lisp_MemoryNode* lisp_MemoryNode_constructor(
    lisp_MemoryNode*, lisp_MemoryNode*, struct lisp_Value*
);
static void lisp_MemoryNode_destructor(lisp_MemoryNode*);


typedef struct lisp_Memory {
    lisp_MemoryNode* root;
    lisp_MemoryNode* tail;
    lisp_u32 size;
} lisp_Memory;

static lisp_Memory* lisp_Memory_constructor(lisp_Memory*);
static void lisp_Memory_destructor(lisp_Memory*);

static lisp_Memory* lisp_Memory_new(void);
static void lisp_Memory_delete(lisp_Memory*);

static struct lisp_Value* lisp_Memory_alloc(lisp_Memory*);
static void lisp_Memory_dealloc(lisp_Memory*, struct lisp_Value*);


#endif
