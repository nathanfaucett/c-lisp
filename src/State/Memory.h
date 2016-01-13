#ifndef __LISP_STATE_MEMORY_H__
#define __LISP_STATE_MEMORY_H__


struct lisp_Value;


typedef struct lisp_MemoryNode {
    struct lisp_MemoryNode* next;
    struct lisp_Value* value;
} lisp_MemoryNode;

static inline lisp_MemoryNode* lisp_MemoryNode_new(lisp_MemoryNode*, lisp_MemoryNode*, struct lisp_Value*);
static inline void lisp_MemoryNode_delete(lisp_MemoryNode*);


typedef struct lisp_Memory {
    lisp_MemoryNode* root;
    lisp_MemoryNode* tail;
    lisp_u32 size;
} lisp_Memory;

static inline lisp_Memory* lisp_Memory_new(lisp_Memory*);
static inline void lisp_Memory_delete(lisp_Memory*);

static inline struct lisp_Value* lisp_Memory_alloc(lisp_Memory*);
static inline void lisp_Memory_dealloc(lisp_Memory*, struct lisp_Value*);


#endif
