#ifndef __LISP_LANG_NUMBER_H__
#define __LISP_LANG_NUMBER_H__


typedef struct lisp_Number {
    struct lisp_Value* value;
    lisp_f64 float_value;
} lisp_Number;

inline static lisp_Number* lisp_Number_new(lisp_Number*, lisp_f64);
inline static lisp_u8* lisp_Number_to_cstring(lisp_Number*);


#endif
