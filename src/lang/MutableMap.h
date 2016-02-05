#ifndef __LISP_LANG_MUTABLE_MAP_H__
#define __LISP_LANG_MUTABLE_MAP_H__


typedef struct lisp_Map {
    lisp_List* entries;
} lisp_Map;


static void lisp_Map_alloc(lisp_State* state, lisp_Object* object);
static void lisp_Map_mark(lisp_Object* object);

static void lisp_Map_init(lisp_State* state, lisp_Map* map, lisp_GCNode* gc_node);

static lisp_size lisp_Map_size(lisp_Map* map);

static lisp_size lisp_Map_index_of(lisp_State* state, lisp_Map* map, lisp_Object* key);

static lisp_bool lisp_Map_has(lisp_State* state, lisp_Map* map, lisp_Object* key);
static lisp_Object* lisp_Map_get(lisp_State* state, lisp_Map* map, lisp_Object* key);

static void lisp_Map_set(lisp_State* state, lisp_Map* map, lisp_Object* key, lisp_Object* object);
static void lisp_Map_remove(lisp_State* state, lisp_Map* map, lisp_Object* key);


#endif
