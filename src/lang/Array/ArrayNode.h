#ifndef __LISP_LANG_ARRAY_NODE_H__
#define __LISP_LANG_ARRAY_NODE_H__


typedef struct lisp_ArrayNode {
    struct lisp_ArrayNode* next;
    lisp_Value* value;
} lisp_ArrayNode;

static lisp_ArrayNode* lisp_ArrayNode_alloc(lisp_ArrayNode* next, lisp_Value* value);
static void lisp_ArrayNode_dealloc(lisp_ArrayNode* node);
static void lisp_ArrayNode_mark(lisp_ArrayNode* node);

static lisp_ArrayNode* lisp_ArrayNode_find_node(lisp_ArrayNode* node, lisp_size index);


#endif
