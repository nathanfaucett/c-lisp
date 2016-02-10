#ifndef __LISP_UTILS_CONVERSIONS_H__
#define __LISP_UTILS_CONVERSIONS_H__


#define LISP_INT_DIGITS 19


static lisp_i64 lisp_ascii_to_i64(lisp_char* ascii);
static lisp_usize lisp_ascii_to_u64(lisp_char* ascii);
static lisp_f64 lisp_ascii_to_f64(lisp_char* ascii);

static lisp_char* lisp_i64_to_ascii(lisp_i64 object);
static lisp_char* lisp_usize_to_ascii(lisp_usize object);
static lisp_char* lisp_f64_to_ascii(lisp_f64 object);

#endif
