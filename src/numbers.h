#ifndef __LISP_NUMBERS_H__
#define __LISP_NUMBERS_H__


static lisp_i32 lisp_atoi(lisp_u8*);
static lisp_f64 lisp_atod(lisp_u8*);

static lisp_u8* lisp_itoa(lisp_i32);
static lisp_u8* lisp_dtoa(lisp_f64);


#endif
