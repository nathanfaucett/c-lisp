#ifndef __LISP_LANG_MUTABLE_LIST_H__
#define __LISP_LANG_MUTABLE_LIST_H__


typedef struct lisp_MutableList {
    lisp_MutableListNode* root;
    lisp_MutableListNode* tail;
    lisp_size size;
} lisp_MutableList;


static void lisp_MutableList_alloc(lisp_State* state, lisp_Value* value);
static void lisp_MutableList_dealloc(lisp_State* state, lisp_Value* value);
static void lisp_MutableList_mark(lisp_Value* value);

static lisp_size lisp_MutableList_index_of(lisp_State* state, lisp_MutableList* list, lisp_Value* key);

static lisp_Value* lisp_MutableList_get(lisp_State* state, lisp_MutableList* list, lisp_size index);
static void lisp_MutableList_set(lisp_MutableList* list, lisp_size index, lisp_Value* value);

static void lisp_MutableList_set_size(lisp_State* state, lisp_MutableList* list, lisp_size new_size);

static void lisp_MutableList_push(lisp_MutableList* list, lisp_Value* value);
static void lisp_MutableList_unshift(lisp_MutableList* list, lisp_Value* value);

static void lisp_MutableList_pop(lisp_MutableList* list);
static void lisp_MutableList_shift(lisp_MutableList* list);
static void lisp_MutableList_remove(lisp_MutableList* list, lisp_size index);

static lisp_bool lisp_MutableList_equal(lisp_State* state, lisp_MutableList* a, lisp_MutableList* b);


static lisp_Value* lisp_MutableList_export_index_of(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static lisp_Value* lisp_MutableList_export_get(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_MutableList_export_set(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static lisp_Value* lisp_MutableList_export_push(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_MutableList_export_unshift(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static lisp_Value* lisp_MutableList_export_pop(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_MutableList_export_shift(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_MutableList_export_remove(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static lisp_Value* lisp_MutableList_export_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_MutableList_export_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static void lisp_MutableList_boot(lisp_State* state);


#endif
