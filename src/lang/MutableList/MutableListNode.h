#ifndef __LISP_LANG_MUTABLE_LIST_NODE_H__
#define __LISP_LANG_MUTABLE_LIST_NODE_H__


typedef struct lisp_MutableListNode {
    struct lisp_MutableListNode* next;
    lisp_Value* value;
} lisp_MutableListNode;

static lisp_MutableListNode* lisp_MutableListNode_alloc(lisp_MutableListNode* next, lisp_Value* value);
static void lisp_MutableListNode_dealloc(lisp_MutableListNode* node);
static void lisp_MutableListNode_mark(lisp_MutableListNode* node);

static lisp_MutableListNode* lisp_MutableListNode_find_node(lisp_MutableListNode* node, lisp_size index);


#endif
