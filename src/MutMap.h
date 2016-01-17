#ifndef __LISP_MAP_H__
#define __LISP_MAP_H__


typedef struct lisp_MutMap {
    lisp_MutList* keys;
    lisp_MutList* values;
} lisp_MutMap;


static lisp_MutMap* lisp_MutMap_constructor(lisp_MutMap*);
static void lisp_MutMap_destructor(lisp_MutMap*);

static lisp_MutMap* lisp_MutMap_new(void);
static void lisp_MutMap_delete(lisp_MutMap*);

static lisp_u32 lisp_MutMap_size(lisp_MutMap*);

static lisp_bool lisp_MutMap_has(lisp_MutMap*, struct lisp_Value*);
static struct lisp_Value* lisp_MutMap_get(lisp_MutMap*, struct lisp_Value*);
static void lisp_MutMap_set(lisp_MutMap*, struct lisp_Value*, struct lisp_Value*);
static void lisp_MutMap_remove(lisp_MutMap*, struct lisp_Value*);


#endif
