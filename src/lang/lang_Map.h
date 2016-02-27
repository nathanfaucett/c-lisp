#ifndef __LISP_LANG_MAP_H__
#define __LISP_LANG_MAP_H__


#define LISP_IDX_MAP_ENTIRES 0


static lisp_Object* lisp_Map_init(lisp_State* state, lisp_Object* map);
static lisp_Object* lisp_Map_new_type(lisp_State* state, lisp_Object* type);

uintsize lisp_Map_size(lisp_State* state, lisp_Object* map);

uintsize lisp_Map_index_of(lisp_State* state, lisp_Object* map, lisp_Object* key);

bool lisp_Map_has(lisp_State* state, lisp_Object* map, lisp_Object* key);
lisp_Object* lisp_Map_get(lisp_State* state, lisp_Object* map, lisp_Object* key);

lisp_Object* lisp_Map_set(lisp_State* state, lisp_Object* map, lisp_Object* key, lisp_Object* object);
lisp_Object* lisp_Map_remove(lisp_State* state, lisp_Object* map, lisp_Object* key);

static void lisp_Map_mut_set(lisp_State* state, lisp_Object* map, lisp_Object* key, lisp_Object* object);
static void lisp_Map_mut_remove(lisp_State* state, lisp_Object* map, lisp_Object* key);


#endif
