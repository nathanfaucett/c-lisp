#ifndef __LISP_LANG_TYPE_H__
#define __LISP_LANG_TYPE_H__


typedef struct lisp_Type {
    lisp_Object* name;
    lisp_Object* attributes;
    lisp_Object* types;
    lisp_Object* super;
    lisp_Object* prototype;
    lisp_Object* template;
    bool abstract;
    bool bytes;
    uintsize size;
    lisp_Object* subtypes;
    void (*alloc)(lisp_State*, struct lisp_Object*);
    void (*mark)(struct lisp_Object*);
} lisp_Type;

static void lisp_Type_alloc(lisp_State* state, lisp_Object* object);
static void lisp_Type_mark(lisp_Object* object);


#endif
