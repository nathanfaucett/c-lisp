#ifndef __LISP_MAP_H__
#define __LISP_MAP_H__


typedef struct lisp_Map {
    lisp_Array* keys;
    lisp_Array* values;
} lisp_Map;


static lisp_Map* lisp_Map_constructor(lisp_Map*);
static void lisp_Map_destructor(lisp_Map*);

static lisp_Map* lisp_Map_new(void);
static void lisp_Map_delete(lisp_Map*);

static lisp_u32 lisp_Map_size(lisp_Map*);

static lisp_bool lisp_Map_has(lisp_Map*, struct lisp_Value*);
static struct lisp_Value* lisp_Map_get(lisp_Map*, struct lisp_Value*);
static void lisp_Map_set(lisp_Map*, struct lisp_Value*, struct lisp_Value*);
static void lisp_Map_remove(lisp_Map*, struct lisp_Value*);


#endif
