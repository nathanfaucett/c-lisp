#ifndef __LISP_LANG_ORDERED_MAP_H__
#define __LISP_LANG_ORDERED_MAP_H__


typedef struct lisp_OrderedMap {
    struct lisp_Value* value;
    lisp_Vector* keys;
    lisp_Vector* values;
} lisp_OrderedMap;


#endif
