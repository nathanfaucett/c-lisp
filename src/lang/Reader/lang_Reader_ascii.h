#ifndef __LISP_LANG_READER_ASCII_H__
#define __LISP_LANG_READER_ASCII_H__


static char lisp_Reader_ascii_index(lisp_Object* reader, char* ascii, uintsize index);
static uintsize lisp_Reader_ascii_next_whitespace(lisp_Object* reader, char* ascii, char ch);
static char* lisp_Reader_ascii_next_token(lisp_State* state, lisp_Object* reader, char* ascii, char ch);
static char lisp_Reader_ascii_read(lisp_State* state, lisp_Object* reader, char* ascii);
static char lisp_Reader_ascii_unread(lisp_State* state, lisp_Object* reader, char* ascii);

lisp_Object* lisp_Reader_ascii_next(lisp_State* state, lisp_Object* reader, char* ascii, char return_on);

static lisp_Object* lisp_Reader_ascii_read_number(lisp_State* state, lisp_Object* reader, char* ascii, char ch);

static lisp_Object* lisp_Reader_ascii_read_list(lisp_State* state, lisp_Object* reader, char* ascii, char ch);
static lisp_Object* lisp_Reader_ascii_read_vector(lisp_State* state, lisp_Object* reader, char* ascii, char ch);
static lisp_Object* lisp_Reader_ascii_read_map(lisp_State* state, lisp_Object* reader, char* ascii, char ch);

static lisp_Object* lisp_Reader_ascii_read_string(lisp_State* state, lisp_Object* reader, char* ascii, char ch);
static lisp_Object* lisp_Reader_ascii_read_char(lisp_State* state, lisp_Object* reader, char* ascii, char ch);

static void lisp_Reader_ascii_read_comment(lisp_State* state, lisp_Object* reader, char* ascii, char ch);

static lisp_Object* lisp_Reader_ascii_read_token(lisp_State* state, lisp_Object* reader, char* ascii, char ch);


#endif
