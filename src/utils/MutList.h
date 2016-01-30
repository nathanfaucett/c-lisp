#ifndef __LISP_UTILS_MUT_LIST_H__
#define __LISP_UTILS_MUT_LIST_H__


typedef struct lisp_MutListNode {
    struct lisp_MutListNode* next;
    void* value;
} lisp_MutListNode;

static lisp_MutListNode* lisp_lisp_MutListNode_constructor(lisp_MutListNode* node, lisp_MutListNode* next, void* value);
static void lisp_MutListNode_destructor(lisp_MutListNode* node);

static lisp_MutListNode* lisp_MutListNode_new(lisp_MutListNode* next, void* value);
static void lisp_MutListNode_delete(lisp_MutListNode* node);

static lisp_MutListNode* lisp_MutListNode_find_node(lisp_MutListNode* node, lisp_size inde);


typedef struct lisp_MutList {
    lisp_MutListNode* root;
    lisp_MutListNode* tail;
    lisp_size size;
} lisp_MutList;


static lisp_MutList* lisp_MutList_constructor(lisp_MutList* mut_list);
static void lisp_MutList_destructor(lisp_MutList* mut_list);

static lisp_MutList* lisp_MutList_new(void);
static void lisp_MutList_delete(lisp_MutList* mut_list);

static lisp_size lisp_MutList_index_of(lisp_MutList* mut_list, void* value);

static void* lisp_MutList_get(lisp_MutList* mut_list, lisp_size index);
static void lisp_MutList_set(lisp_MutList* mut_list, lisp_size index, void* value);

static void lisp_MutList_push(lisp_MutList* mut_list, void* value);
static void lisp_MutList_unshift(lisp_MutList* mut_list, void* value);

static void* lisp_MutList_pop(lisp_MutList* mut_list);
static void* lisp_MutList_shift(lisp_MutList* mut_list);
static void lisp_MutList_remove(lisp_MutList* mut_list, lisp_size index);


#endif
