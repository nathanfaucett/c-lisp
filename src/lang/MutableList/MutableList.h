#ifndef __LISP_LANG_MUTABLE_LIST_H__
#define __LISP_LANG_MUTABLE_LIST_H__


typedef struct lisp_MutableList {
    lisp_GCNode* gc_node;
    lisp_MutableListNode* root;
    lisp_MutableListNode* tail;
    lisp_size size;
} lisp_MutableList;


static void lisp_MutableList_alloc(lisp_State* state, lisp_Object* object);
static void lisp_MutableList_mark(lisp_Object* object);

static void lisp_MutableList_init(lisp_MutableList* list, lisp_GCNode* gc_node);

static lisp_Object* lisp_MutableList_get(lisp_State* state, lisp_MutableList* list, lisp_size index);
static void lisp_MutableList_set(lisp_MutableList* list, lisp_size index, lisp_Object* object);

static void lisp_MutableList_set_size(lisp_State* state, lisp_MutableList* list, lisp_size new_size);

static void lisp_MutableList_push(lisp_State* state, lisp_MutableList* list, lisp_Object* object);
static void lisp_MutableList_unshift(lisp_State* state, lisp_MutableList* list, lisp_Object* object);

static void lisp_MutableList_pop(lisp_State* state, lisp_MutableList* list);
static void lisp_MutableList_shift(lisp_State* state, lisp_MutableList* list);
static void lisp_MutableList_remove(lisp_State* state, lisp_MutableList* list, lisp_size index);


#endif
