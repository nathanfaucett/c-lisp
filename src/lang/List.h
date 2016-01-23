#ifndef __LISP_LANG_LIST_H__
#define __LISP_LANG_LIST_H__


typedef struct lisp_ListNode {
    lisp_u64 ref_count;
    struct lisp_ListNode* next;
    struct lisp_Value* value;
} lisp_ListNode;

static lisp_ListNode* lisp_ListNode_constructor(lisp_ListNode* node, lisp_ListNode* next, struct lisp_Value* value);
static void lisp_ListNode_destructor(lisp_State* state, lisp_ListNode* node);

static lisp_ListNode* lisp_ListNode_new(lisp_ListNode* next, struct lisp_Value* value);
static void lisp_ListNode_delete(lisp_State* state, lisp_ListNode* node);

static lisp_ListNode* lisp_ListNode_find_node(lisp_ListNode* node, lisp_u64 index);

static lisp_ListNode* lisp_ListNode_push(lisp_ListNode*, lisp_ListNode*);

static void lisp_ListNode_ref(lisp_ListNode* node);
static void lisp_ListNode_deref(lisp_State* state, lisp_ListNode* node);


typedef struct lisp_List {
    struct lisp_Value* value;

    lisp_ListNode* root;
    lisp_ListNode* tail;
    lisp_u64 size;
} lisp_List;

static void lisp_List_alloc(lisp_State* state, struct lisp_Value* value);
static void lisp_List_dealloc(lisp_State* state, struct lisp_Value* value);

static lisp_List* lisp_List_constructor(lisp_List* list, lisp_ListNode* root, lisp_ListNode* tail, lisp_u64 size);

static struct lisp_Value* lisp_List_from_mut_list(lisp_State* state, lisp_MutList* mut_list);

static lisp_ListNode* lisp_List_find_node(lisp_List*, lisp_u64);
static struct lisp_Value* lisp_List_get(lisp_State*, lisp_List*, lisp_u64);

static struct lisp_Value* lisp_List_push(lisp_State*, lisp_List*, struct lisp_Value*);
static struct lisp_Value* lisp_List_unshift(lisp_State*, lisp_List*, struct lisp_Value*);

static struct lisp_Value* lisp_List_pop(lisp_State*, lisp_List*);
static struct lisp_Value* lisp_List_shift(lisp_State*, lisp_List*);
static struct lisp_Value* lisp_List_after(lisp_State*, lisp_List*, lisp_u64);

static struct lisp_Value* lisp_List_set(lisp_State*, lisp_List*, lisp_u64 index, struct lisp_Value*);

static lisp_ListNode* lisp_List_copy_from_to(lisp_ListNode*, lisp_ListNode*, lisp_ListNode*);
static struct lisp_Value* lisp_List_remove(lisp_State*, lisp_List*, lisp_u64);


#endif
