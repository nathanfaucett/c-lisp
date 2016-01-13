#ifndef __LISP_LISP_H__
#define __LISP_LISP_H__


#include <stdlib.h>
#include "./types.h"


#define true 1
#define false 0


#define CREATE_ARRAY_COPY_PROTO(name, TypeA, TypeB, Return)\
inline static Return name ## _array_copy(TypeA, TypeB, lisp_u32, lisp_u32, lisp_u32);

#define CREATE_ARRAY_COPY(name, TypeA, TypeB, Return)\
inline static Return name ## _array_copy(TypeA a, TypeB b, lisp_u32 start, lisp_u32 end, lisp_u32 dest) {\
    for (lisp_u32 i = start, il = end, j = dest; i < il; i++, j++) {\
        a[j] = b[i];\
    }\
    return a;\
}\

CREATE_ARRAY_COPY_PROTO(str, lisp_u8*, lisp_u8*, lisp_u8*);


inline static lisp_u32 str_size(lisp_u8*);
inline static lisp_u8* str_copy(lisp_u8*, lisp_u8*);
inline static lisp_u8* str_clone(lisp_u8*);

#endif
