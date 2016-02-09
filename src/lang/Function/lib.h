#ifndef __LISP_LANG_FUNCTION_LIB_H__
#define __LISP_LANG_FUNCTION_LIB_H__


#include "./Function.h"
#include "./Macro.h"
#include "./Native.h"


static lisp_Object* lisp_function_call(lisp_State* state, lisp_Object* fn, lisp_Object* args, lisp_Object* scope);


#endif
