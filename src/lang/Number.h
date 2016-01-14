#ifndef __LISP_LANG_NUMBER_H__
#define __LISP_LANG_NUMBER_H__


typedef struct lisp_Number {
    struct lisp_Value* value;
    lisp_bool is_f64;
    lisp_i32 i32;
    lisp_f64 f64;
} lisp_Number;

inline static lisp_Number* lisp_Number_from_i32(lisp_Number*, lisp_i32);
inline static lisp_Number* lisp_Number_from_f64(lisp_Number*, lisp_f64);

inline static lisp_i32 lisp_Number_get_i32(lisp_Number*);
inline static lisp_f64 lisp_Number_get_f64(lisp_Number*);

inline static struct lisp_Value* lisp_Number_to_string(lisp_State*, lisp_Number*);


#endif
