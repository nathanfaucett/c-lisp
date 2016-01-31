#ifndef __LISP_LANG_LIST_NODE_H__
#define __LISP_LANG_LIST_NODE_H__


typedef struct lisp_ListNode {
    lisp_Value* next;
    lisp_Value* value;
} lisp_ListNode;

static void lisp_ListNode_alloc(lisp_State* state, lisp_Value* value);
static void lisp_ListNode_mark(lisp_Value* value);

static lisp_Value* lisp_ListNode_find_node(lisp_Value* node, lisp_size index);
static lisp_Value* lisp_ListNode_copy_from_to(lisp_State* state, lisp_Value* from, lisp_Value* to, lisp_Value* new_node);
static lisp_Value* lisp_ListNode_push(lisp_State* state, lisp_Value* node_value, lisp_Value* last_node_value);


#endif
