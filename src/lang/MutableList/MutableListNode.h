#ifndef __LISP_LANG_MUTABLE_LIST_NODE_H__
#define __LISP_LANG_MUTABLE_LIST_NODE_H__


typedef struct lisp_MutableListNode {
    struct lisp_MutableListNode* next;
    lisp_Object* object;
} lisp_MutableListNode;

static lisp_MutableListNode* lisp_MutableListNode_alloc(lisp_State* state, lisp_GCNode* gc_node, lisp_MutableListNode* next, lisp_Object* object);
static void lisp_MutableListNode_dealloc(lisp_State* state, lisp_GCNode* gc_node, lisp_MutableListNode* node);
static void lisp_MutableListNode_mark(lisp_MutableListNode* node);

static lisp_MutableListNode* lisp_MutableListNode_find_node(lisp_MutableListNode* node, lisp_size index);


#endif
