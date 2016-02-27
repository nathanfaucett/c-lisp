#ifndef __LISP_LANG_TYPE_H__
#define __LISP_LANG_TYPE_H__


#define LISP_IDX_TYPE_NAME 0
#define LISP_IDX_TYPE_ATTRIBUTES 1
#define LISP_IDX_TYPE_TYPES 2
#define LISP_IDX_TYPE_SIZE 3
#define LISP_IDX_TYPE_SUPER 4
#define LISP_IDX_TYPE_PROTOTYPE 5
#define LISP_IDX_TYPE_TEMPLATE 6
#define LISP_IDX_TYPE_ABSTRACT 7
#define LISP_IDX_TYPE_BYTES 8
#define LISP_IDX_TYPE_IMMUTABLE 9
#define LISP_IDX_TYPE_SUBTYPES 10
#define LISP_TYPE_SIZE 11

static void lisp_Type_boot(lisp_State* state, lisp_Object* Type);


#endif
