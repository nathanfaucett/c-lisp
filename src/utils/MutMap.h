#ifndef __LISP_UTILS_MUT_MAP_H__
#define __LISP_UTILS_MUT_MAP_H__


typedef struct lisp_MutMap {
    lisp_MutList* entries;
} lisp_MutMap;


static lisp_MutMap* lisp_MutMap_constructor(lisp_MutMap* map);
static void lisp_MutMap_destructor(lisp_MutMap* map);

static lisp_MutMap* lisp_MutMap_new(void);
static void lisp_MutMap_delete(lisp_MutMap* map);

static lisp_u64 lisp_MutMap_size(lisp_MutMap* map);

static lisp_u64 lisp_MutMap_index_of(lisp_MutMap* map, void* key);

static lisp_bool lisp_MutMap_has(lisp_MutMap* map, void* key);
static void* lisp_MutMap_get(lisp_MutMap* map, void* key);
static void lisp_MutMap_set(lisp_MutMap* map, void* key, void* value);
static void lisp_MutMap_remove(lisp_MutMap* map, void* key);


#endif
