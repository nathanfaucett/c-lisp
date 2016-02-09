#ifndef __LISP_TYPES_H__
#define __LISP_TYPES_H__


typedef unsigned char lisp_byte;
typedef lisp_byte lisp_bool;
typedef char lisp_char;

typedef signed long int lisp_isize;
typedef signed char lisp_i8;
typedef signed int lisp_i16;
typedef signed long int lisp_i32;
typedef signed long long int lisp_i64;

typedef unsigned long int lisp_usize;
typedef unsigned char lisp_u8;
typedef unsigned int lisp_u16;
typedef unsigned long int lisp_u32;
typedef unsigned long long int lisp_u64;

typedef float lisp_f32;
typedef double lisp_f64;

typedef size_t lisp_size;


#define LISP_TRUE ((lisp_bool)1)
#define LISP_FALSE ((lisp_bool)0)


#endif
