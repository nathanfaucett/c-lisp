#ifndef __LISP_LANG_LIST_NODE_H__
#define __LISP_LANG_LIST_NODE_H__


typedef struct lisp_ListNode {
    lisp_Object* next;
    lisp_Object* object;
} lisp_ListNode;

static void lisp_ListNode_alloc(lisp_State* state, lisp_Object* object);
static void lisp_ListNode_mark(lisp_Object* object);

static lisp_Object* lisp_ListNode_find_node(lisp_Object* node, lisp_size index);
static lisp_Object* lisp_ListNode_copy_from_to(lisp_State* state, lisp_Object* from, lisp_Object* to, lisp_Object* new_node);
static lisp_Object* lisp_ListNode_push(lisp_State* state, lisp_Object* node_object, lisp_Object* last_node_object);


#endif
