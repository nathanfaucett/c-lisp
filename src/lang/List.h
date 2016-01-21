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

static void lisp_ListNode_ref(lisp_ListNode* node);
static void lisp_ListNode_deref(lisp_State* state, lisp_ListNode* node);


typedef struct lisp_List {
    lisp_ListNode* root;
    lisp_ListNode* tail;
    lisp_u64 size;
} lisp_List;

static void lisp_List_alloc(lisp_State* state, struct lisp_Value* value);
static void lisp_List_dealloc(lisp_State* state, struct lisp_Value* value);


#endif
