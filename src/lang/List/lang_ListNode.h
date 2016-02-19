#ifndef __LISP_LANG_LIST_NODE_H__
#define __LISP_LANG_LIST_NODE_H__


#define LISP_IDX_LIST_NODE_NEXT 0
#define LISP_IDX_LIST_NODE_VALUE 1


static lisp_Object* lisp_ListNode_new(lisp_State* state, lisp_Object* next, lisp_Object* value);

static lisp_Object* lisp_ListNode_find_node(lisp_Object* node, uintsize index);
static lisp_Object* lisp_ListNode_copy_from_to(lisp_State* state, lisp_Object* from, lisp_Object* to, lisp_Object* new_node);
static lisp_Object* lisp_ListNode_push(lisp_State* state, lisp_Object* node, lisp_Object* last_node);


#endif
