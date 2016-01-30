#ifndef __LISP_UTILS_CSTRING_H__
#define __LISP_UTILS_CSTRING_H__


static lisp_size lisp_ascii_size(lisp_char* ascii);
static lisp_char* lisp_ascii_copy(lisp_char* a, lisp_char* b);
static lisp_char* lisp_ascii_clone(lisp_char* ascii);
static lisp_size lisp_ascii_index_of(lisp_char* ascii, lisp_char ch);
static lisp_bool lisp_ascii_equal(lisp_char* a, lisp_char* b);

static lisp_size lisp_utf8_size(lisp_u32* utf8);
static lisp_u32* lisp_utf8_copy(lisp_u32* a, lisp_u32* b);
static lisp_u32* lisp_utf8_clone(lisp_u32* utf8);
static lisp_size lisp_utf8_index_of(lisp_u32* utf8, lisp_u32 ch);
static lisp_bool lisp_utf8_equal(lisp_u32* a, lisp_u32* b);

static lisp_bool lisp_ascii_utf8_equal(lisp_u32* a, lisp_char* b);


#endif
