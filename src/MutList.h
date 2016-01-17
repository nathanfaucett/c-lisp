#ifndef __LISP_MUT_LIST_H__
#define __LISP_MUT_LIST_H__


typedef struct lisp_MutListNode {
    struct lisp_MutListNode* next;
    struct lisp_Value* value;
} lisp_MutListNode;

static lisp_MutListNode* lisp_lisp_MutListNode_constructor(lisp_MutListNode*, lisp_MutListNode*, struct lisp_Value*);
static void lisp_MutListNode_destructor(lisp_MutListNode*);

static lisp_MutListNode* lisp_MutListNode_new(lisp_MutListNode*, struct lisp_Value*);
static void lisp_MutListNode_delete(lisp_MutListNode*);

static lisp_MutListNode* lisp_MutListNode_find_node(lisp_MutListNode*, lisp_u32);


typedef struct lisp_MutList {
    lisp_u32 size;
    lisp_MutListNode* root;
    lisp_MutListNode* tail;
} lisp_MutList;


static lisp_MutList* lisp_MutList_constructor(lisp_MutList*);
static void lisp_MutList_destructor(lisp_MutList*);

static lisp_MutList* lisp_MutList_new(void);
static void lisp_MutList_delete(lisp_MutList*);

static lisp_u32 lisp_MutList_size(lisp_MutList*);
static lisp_i32 lisp_MutList_index_of(lisp_MutList*, struct lisp_Value*);

static struct lisp_Value* lisp_MutList_get(lisp_MutList*, lisp_u32);
static void lisp_MutList_set(lisp_MutList*, lisp_u32, struct lisp_Value*);

static void lisp_MutList_push(lisp_MutList*, struct lisp_Value*);
static void lisp_MutList_unshift(lisp_MutList*, struct lisp_Value*);

static struct lisp_Value* lisp_MutList_pop(lisp_MutList*);
static struct lisp_Value* lisp_MutList_shift(lisp_MutList*);
static void lisp_MutList_remove(lisp_MutList*, lisp_u32);


#endif
