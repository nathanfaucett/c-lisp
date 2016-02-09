#ifndef __LISP_LANG_NUMBER_H__
#define __LISP_LANG_NUMBER_H__


static lisp_Object* lisp_Number_UInt(lisp_State* state, lisp_usize value);
static lisp_Object* lisp_Number_Int(lisp_State* state, lisp_isize value);
static lisp_size lisp_Number_get_UInt(lisp_State* state, lisp_Object* value);


#endif
