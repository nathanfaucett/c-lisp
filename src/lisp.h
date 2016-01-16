#ifndef __LISP_LISP_H__
#define __LISP_LISP_H__


#include <stdlib.h>
#include "./types.h"


#define LISP_TRUE 1
#define LISP_FALSE 0

/* forward declare for function prototypes */
struct lisp_Value;


#define CREATE_ARRAY_COPY_PROTO(name, TypeA, TypeB, Return)\
static Return lisp_ ## name ## _copy(TypeA, TypeB, lisp_u32, lisp_u32, lisp_u32);

#define CREATE_ARRAY_COPY(name, TypeA, TypeB, Return)\
static Return lisp_ ## name ## _copy(TypeA a, TypeB b, lisp_u32 start, lisp_u32 end, lisp_u32 dest) {\
    for (lisp_u32 i = start, il = end, j = dest; i < il; i++, j++) {\
        a[j] = b[i];\
    }\
    return a;\
}\

CREATE_ARRAY_COPY_PROTO(cstr, lisp_u8*, lisp_u8*, lisp_u8*);
CREATE_ARRAY_COPY_PROTO(values, struct lisp_Value**, struct lisp_Value**, struct lisp_Value**);
CREATE_ARRAY_COPY_PROTO(vector_nodes, struct lisp_VectorNode**, struct lisp_VectorNode**, struct lisp_VectorNode**);


static lisp_u32 lisp_cstring_size(lisp_u8*);
static lisp_u8* lisp_cstring_copy(lisp_u8*, lisp_u8*);
static lisp_u8* lisp_cstring_clone(lisp_u8*);
static lisp_bool lisp_cstring_equal(lisp_u8*, lisp_u8*);
static void lisp_cstring_reverse(lisp_u8*);

#endif
