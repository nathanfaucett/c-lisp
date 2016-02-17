#ifndef __LISP_H__
#define __LISP_H__


#ifdef __cplusplus
extern "C" {
#endif


#include "types/lib.h"


extern void* malloc(uintsize size);
extern void free(void* ptr);


#include "gc_lib.h"
#include "core_lib.h"
#include "lang_lib.h"


#ifdef __cplusplus
}
#endif


#endif
