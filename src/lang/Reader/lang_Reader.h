#ifndef __LISP_LANG_READER_H__
#define __LISP_LANG_READER_H__


#define LISP_IDX_READER_INDEX 0
#define LISP_IDX_READER_COLUMN 1
#define LISP_IDX_READER_ROW 2
#define LISP_IDX_READER_LAST_COLUMN 3


static bool lisp_is_whitespace(uint32 ch);
static bool lisp_is_numeric(uint32 ch);
static uint32 lisp_escape(uint32 ch);
static uintsize lisp_ascii_index_of(char* ascii, char ch);
static bool lisp_cstring_equal(char* a, char* b);

lisp_Object* lisp_Reader_new(lisp_State* state);
static bool lisp_Reader_is_marco(uint32 ch);


#endif
