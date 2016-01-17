#ifndef __LISP_LANG_LIST_H__
#define __LISP_LANG_LIST_H__


typedef struct lisp_ListNode {
    lisp_u32 ref_count;
    struct lisp_ListNode* next;
    struct lisp_Value* value;
} lisp_ListNode;

static lisp_ListNode* lisp_ListNode_constructor(lisp_ListNode*, lisp_ListNode*, struct lisp_Value*);

static lisp_ListNode* lisp_ListNode_new(lisp_ListNode*, struct lisp_Value*);
static void lisp_ListNode_delete(lisp_State*, lisp_ListNode*);

static void lisp_ListNode_ref(lisp_ListNode*);
static void lisp_ListNode_deref(lisp_State*, lisp_ListNode*);


typedef struct lisp_List {
    struct lisp_Value* value;
    lisp_ListNode* root;
    lisp_ListNode* tail;
    lisp_u32 size;
} lisp_List;

static lisp_List* lisp_List_constructor(lisp_List*, lisp_ListNode*, lisp_ListNode*, lisp_u32);
static void lisp_List_destructor(lisp_State*, lisp_List*);

static struct lisp_Value* lisp_List_from_mut_list(lisp_State*, lisp_MutList*);
static struct lisp_Value* lisp_List_internal_new(lisp_State*);

static lisp_u32 lisp_List_size(lisp_List*);

static lisp_ListNode* lisp_List_get_node(lisp_ListNode*, lisp_u32);
static lisp_ListNode* lisp_List_find_node(lisp_List*, lisp_u32);
static struct lisp_Value* lisp_List_get(lisp_State*, lisp_List*, lisp_u32);

static lisp_ListNode* lisp_ListNode_push(lisp_ListNode*, lisp_ListNode*);

static struct lisp_Value* lisp_List_push(lisp_State*, lisp_List*, struct lisp_Value*);
static struct lisp_Value* lisp_List_unshift(lisp_State*, lisp_List*, struct lisp_Value*);

static struct lisp_Value* lisp_List_pop(lisp_State*, lisp_List*);
static struct lisp_Value* lisp_List_shift(lisp_State*, lisp_List*);

static lisp_ListNode* lisp_List_copy_from_to(lisp_ListNode*, lisp_ListNode*, lisp_ListNode*);
static struct lisp_Value* lisp_List_remove_index(lisp_State*, lisp_List*, lisp_u32);
static struct lisp_Value* lisp_List_remove(lisp_State*, lisp_List*, struct lisp_Value*);

static struct lisp_Value* lisp_List_to_string(lisp_State*, lisp_List*);

static lisp_bool lisp_List_equal(lisp_List*, lisp_List*);

#endif
