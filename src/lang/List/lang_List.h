#ifndef __LISP_LANG_LIST_H__
#define __LISP_LANG_LIST_H__


typedef struct lisp_List {
    lisp_Object* self;
    lisp_ListNode* root;
    lisp_ListNode* tail;
    uintsize size;
} lisp_List;


static void lisp_List_alloc(lisp_State* state, lisp_Object* object);
static void lisp_List_mark(lisp_Object* object);

static lisp_Object* lisp_List_new(lisp_State* state, lisp_Object* template);
static lisp_Object* lisp_List_new_type(lisp_State* state, lisp_Object* Type);

static lisp_ListNode* lisp_List_find_node(lisp_List* list, uintsize index);
static uintsize lisp_List_index_of(lisp_State* state, lisp_List* list, lisp_Object* key);

static lisp_Object* lisp_List_concat(lisp_State* state, lisp_List* a, lisp_List* b);

static void lisp_List_mut_set_size(lisp_State* state, lisp_List* list, uintsize new_size);

static lisp_Object* lisp_List_get(lisp_State* state, lisp_List* list, uintsize index);
static lisp_Object* lisp_List_set(lisp_State* state, lisp_List* list, uintsize index, lisp_Object* object);
static void lisp_List_mut_set(lisp_List* list, uintsize index, lisp_Object* object);

static lisp_Object* lisp_List_push(lisp_State* state, lisp_List* list, lisp_Object* object);
static void lisp_List_mut_push(lisp_State* state, lisp_List* list, lisp_Object* object);

static lisp_Object* lisp_List_unshift(lisp_State* state, lisp_List* list, lisp_Object* object);

static lisp_Object* lisp_List_pop(lisp_State* state, lisp_List* list);
static lisp_Object* lisp_List_shift(lisp_State* state, lisp_List* list);
static lisp_Object* lisp_List_remove(lisp_State* state, lisp_List* list, uintsize index);

static void lisp_List_mut_pop(lisp_List* list);
static void lisp_List_mut_shift(lisp_List* list);
static void lisp_List_mut_remove(lisp_List* list, uintsize index);

static bool lisp_List_equal(lisp_State* state, lisp_List* a, lisp_List* b);


#endif
