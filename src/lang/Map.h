#ifndef __LISP_LANG_MAP_H__
#define __LISP_LANG_MAP_H__


typedef struct lisp_Map {
    lisp_Seq* entries;
} lisp_Map;


static void lisp_Map_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Map_dealloc(lisp_State* state, lisp_Value* value);
static void lisp_Map_mark(lisp_Value* value);

static lisp_size lisp_Map_size(lisp_Map* map);

static lisp_size lisp_Map_index_of(lisp_State* state, lisp_Map* map, lisp_Value* key);

static lisp_bool lisp_Map_has(lisp_State* state, lisp_Map* map, lisp_Value* key);
static lisp_Value* lisp_Map_get(lisp_State* state, lisp_Map* map, lisp_Value* key);
static void lisp_Map_set(lisp_State* state, lisp_Map* map, lisp_Value* key, lisp_Value* value);
static void lisp_Map_remove(lisp_State* state, lisp_Map* map, lisp_Value* key);

static lisp_bool lisp_Map_equal(lisp_State* state, lisp_Map* a, lisp_Map* b);


#endif
