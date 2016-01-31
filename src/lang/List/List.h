#ifndef __LISP_LANG_LIST_H__
#define __LISP_LANG_LIST_H__


typedef struct lisp_List {
    lisp_Value* self;
    lisp_Value* root;
    lisp_Value* tail;
    lisp_size size;
} lisp_List;


static void lisp_List_alloc(lisp_State* state, lisp_Value* value);
static void lisp_List_mark(lisp_Value* value);

static lisp_Value* lisp_List_from_seq(lisp_State* state, lisp_Seq* seq);

static lisp_Value* lisp_List_find_node(lisp_List* list, lisp_size index);
static lisp_size lisp_List_index_of(lisp_State* state, lisp_List* list, lisp_Value* key);

static lisp_Value* lisp_List_get(lisp_State* state, lisp_List* list, lisp_size index);
static lisp_Value* lisp_List_set(lisp_State* state, lisp_List* list, lisp_size index, lisp_Value* value);

static lisp_Value* lisp_List_push(lisp_State* state, lisp_List* list, lisp_Value* value);
static lisp_Value* lisp_List_unshift(lisp_State* state, lisp_List* list, lisp_Value* value);

static lisp_Value* lisp_List_pop(lisp_State* state, lisp_List* list);
static lisp_Value* lisp_List_shift(lisp_State* state, lisp_List* list);
static lisp_Value* lisp_List_remove(lisp_State* state, lisp_List* list, lisp_size index);

static lisp_bool lisp_List_equal(lisp_State* state, lisp_List* a, lisp_List* b);


#endif
