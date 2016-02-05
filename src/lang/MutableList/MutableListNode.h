#ifndef __LISP_LANG_MUTABLE_LIST_NODE_H__
#define __LISP_LANG_MUTABLE_LIST_NODE_H__


typedef struct lisp_ListNode {
    struct lisp_ListNode* next;
    lisp_Object* object;
} lisp_ListNode;

static lisp_ListNode* lisp_ListNode_alloc(lisp_State* state, lisp_GCNode* gc_node, lisp_ListNode* next, lisp_Object* object);
static void lisp_ListNode_dealloc(lisp_State* state, lisp_GCNode* gc_node, lisp_ListNode* node);
static void lisp_ListNode_mark(lisp_ListNode* node);

static lisp_ListNode* lisp_ListNode_find_node(lisp_ListNode* node, lisp_size index);


#endif
