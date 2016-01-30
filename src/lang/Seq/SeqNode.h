#ifndef __LISP_LANG_SEQ_NODE_H__
#define __LISP_LANG_SEQ_NODE_H__


typedef struct lisp_SeqNode {
    struct lisp_SeqNode* next;
    lisp_Value* value;
} lisp_SeqNode;

static lisp_SeqNode* lisp_SeqNode_alloc(lisp_SeqNode* next, lisp_Value* value);
static void lisp_SeqNode_dealloc(lisp_SeqNode* node);
static void lisp_SeqNode_mark(lisp_SeqNode* node);

static lisp_SeqNode* lisp_SeqNode_find_node(lisp_SeqNode* node, lisp_size index);


#endif
