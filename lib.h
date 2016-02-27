#ifndef __LISP_H__
#define __LISP_H__


#ifdef __cplusplus
extern "C" {
#endif


#include "types/lib.h"
#include "string_to_float/lib.h"
#include "string_to_int/lib.h"


extern void* malloc(uintsize size);
extern void free(void* ptr);


#include "gc_lib.h"
#include "State.h"
#include "lang_lib.h"
#include "boot.h"


#ifdef __cplusplus
}
#endif


#endif
