#ifndef __LISP_UTILS_CSTRING_H__
#define __LISP_UTILS_CSTRING_H__


static lisp_u64 lisp_cstring_size(lisp_char* cstring);
static lisp_char* lisp_cstring_copy(lisp_char* a, lisp_char* b);
static lisp_char* lisp_cstring_clone(lisp_char* cstring);
static lisp_u64 lisp_cstring_index_of(lisp_char* cstring, lisp_char ch);
static lisp_bool lisp_cstring_equal(lisp_char* a, lisp_char* b);

static lisp_bool lisp_u32_char_equal(lisp_u32* a, lisp_char* b);


#endif
