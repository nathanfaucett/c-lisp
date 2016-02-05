#ifndef __LISP_LANG_MUTABLE_MAP_H__
#define __LISP_LANG_MUTABLE_MAP_H__


typedef struct lisp_MutableMap {
    lisp_MutableList* entries;
} lisp_MutableMap;


static void lisp_MutableMap_alloc(lisp_State* state, lisp_Object* object);
static void lisp_MutableMap_mark(lisp_Object* object);

static void lisp_MutableMap_init(lisp_State* state, lisp_MutableMap* map, lisp_GCNode* gc_node);

static lisp_size lisp_MutableMap_size(lisp_MutableMap* map);

static lisp_size lisp_MutableMap_index_of(lisp_State* state, lisp_MutableMap* map, lisp_Object* key);

static lisp_bool lisp_MutableMap_has(lisp_State* state, lisp_MutableMap* map, lisp_Object* key);
static lisp_Object* lisp_MutableMap_get(lisp_State* state, lisp_MutableMap* map, lisp_Object* key);

static void lisp_MutableMap_set(lisp_State* state, lisp_MutableMap* map, lisp_Object* key, lisp_Object* object);
static void lisp_MutableMap_remove(lisp_State* state, lisp_MutableMap* map, lisp_Object* key);


#endif
