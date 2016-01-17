#ifndef __LISP_LANG_MAP_H__
#define __LISP_LANG_MAP_H__


typedef struct lisp_Map {
    struct lisp_Value* value;
    lisp_Vector* keys;
    lisp_Vector* values;
} lisp_Map;


#endif
