#ifndef __LISP_LANG_LIST_NODE_H__
#define __LISP_LANG_LIST_NODE_H__


typedef struct lisp_ListNode {
    lisp_GCHeader* gc_header;
    struct lisp_ListNode* next;
    lisp_Object* value;
} lisp_ListNode;

static void lisp_ListNode_mark(lisp_ListNode* node);

static lisp_ListNode* lisp_ListNode_new(lisp_State* state, lisp_ListNode* next, lisp_Object* value);

static lisp_ListNode* lisp_ListNode_find_node(lisp_ListNode* node, uintsize index);
static lisp_ListNode* lisp_ListNode_copy_from_to(lisp_State* state, lisp_ListNode* from, lisp_ListNode* to, lisp_ListNode* new_node);
static lisp_ListNode* lisp_ListNode_push(lisp_State* state, lisp_ListNode* node, lisp_ListNode* last_node);


#endif
