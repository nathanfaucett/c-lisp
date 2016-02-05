#ifndef __LISP_LANG_MUTABLE_LIST_H__
#define __LISP_LANG_MUTABLE_LIST_H__


typedef struct lisp_List {
    lisp_GCNode* gc_node;
    lisp_ListNode* root;
    lisp_ListNode* tail;
    lisp_size size;
} lisp_List;


static void lisp_List_alloc(lisp_State* state, lisp_Object* object);
static void lisp_List_mark(lisp_Object* object);

static void lisp_List_init(lisp_List* list, lisp_GCNode* gc_node);

static lisp_Object* lisp_List_get(lisp_State* state, lisp_List* list, lisp_size index);
static void lisp_List_set(lisp_List* list, lisp_size index, lisp_Object* object);

static void lisp_List_set_size(lisp_State* state, lisp_List* list, lisp_size new_size);

static void lisp_List_push(lisp_State* state, lisp_List* list, lisp_Object* object);
static void lisp_List_unshift(lisp_State* state, lisp_List* list, lisp_Object* object);

static void lisp_List_pop(lisp_State* state, lisp_List* list);
static void lisp_List_shift(lisp_State* state, lisp_List* list);
static void lisp_List_remove(lisp_State* state, lisp_List* list, lisp_size index);


#endif
