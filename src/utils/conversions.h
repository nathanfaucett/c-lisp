#ifndef __LISP_UTILS_CONVERSIONS_H__
#define __LISP_UTILS_CONVERSIONS_H__


#define LISP_INT_DIGITS 19


static lisp_i32 lisp_cstring_to_i32(lisp_char* cstring);
static lisp_f64 lisp_cstring_to_f64(lisp_char* cstring);

static lisp_char* lisp_i32_to_cstring(lisp_i32 value);
static lisp_char* lisp_f64_to_cstring(lisp_f64 value);

#endif
