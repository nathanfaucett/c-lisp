#ifndef __LISP_LANG_NIL_H__
#define __LISP_LANG_NIL_H__


typedef struct lisp_Nil {
    struct lisp_Value* value;
} lisp_Nil;

inline static struct lisp_Value* lisp_Nil_to_string(lisp_State* state);


#endif
