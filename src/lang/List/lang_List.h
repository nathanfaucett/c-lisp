#ifndef __LISP_LANG_LIST_H__
#define __LISP_LANG_LIST_H__


#define LISP_IDX_LIST_ROOT 0
#define LISP_IDX_LIST_TAIL 1
#define LISP_IDX_LIST_SIZE 2


static lisp_Object* lisp_List_init(lisp_State* state, lisp_Object* map);
static lisp_Object* lisp_List_new_type(lisp_State* state, lisp_Object* type);

static lisp_Object* lisp_List_find_node(lisp_State* state, lisp_Object* list, uintsize index);
static uintsize lisp_List_index_of(lisp_State* state, lisp_Object* list, lisp_Object* key);

static lisp_Object* lisp_List_concat(lisp_State* state, lisp_Object* a, lisp_Object* b);

static void lisp_List_mut_set_size(lisp_State* state, lisp_Object* list, uintsize new_size);

static lisp_Object* lisp_List_get(lisp_State* state, lisp_Object* list, uintsize index);
static lisp_Object* lisp_List_set(lisp_State* state, lisp_Object* list, uintsize index, lisp_Object* object);
static void lisp_List_mut_set(lisp_State* state, lisp_Object* list, uintsize index, lisp_Object* object);

static lisp_Object* lisp_List_push(lisp_State* state, lisp_Object* list, lisp_Object* object);
static void lisp_List_mut_push(lisp_State* state, lisp_Object* list, lisp_Object* object);

static lisp_Object* lisp_List_unshift(lisp_State* state, lisp_Object* list, lisp_Object* object);

static lisp_Object* lisp_List_pop(lisp_State* state, lisp_Object* list);
static lisp_Object* lisp_List_shift(lisp_State* state, lisp_Object* list);
static lisp_Object* lisp_List_remove(lisp_State* state, lisp_Object* list, uintsize index);

static void lisp_List_mut_pop(lisp_State* state, lisp_Object* list);
static void lisp_List_mut_shift(lisp_State* state, lisp_Object* list);
static void lisp_List_mut_remove(lisp_State* state, lisp_Object* list, uintsize index);


#endif
