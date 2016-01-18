#ifndef __LISP_CORE_READER_H__
#define __LISP_CORE_READER_H__


typedef struct lisp_Reader {
    struct lisp_State* state;
    lisp_u8* cstring;
    lisp_u64 index;
    lisp_u64 column;
    lisp_u64 row;
} lisp_Reader;


static lisp_Reader* lisp_Reader_constructor(lisp_Reader*, struct lisp_State*, lisp_u8*);

static lisp_Reader* lisp_Reader_new(struct lisp_State*, lisp_u8*);
static void lisp_Reader_delete(lisp_Reader*);

static lisp_bool lisp_Reader_is_whitespace(lisp_u8);
static lisp_bool lisp_Reader_is_numeric(lisp_u8);
static lisp_bool lisp_Reader_is_marco(lisp_u8);
static lisp_u8 lisp_Reader_escape(lisp_u8);

static lisp_u8 lisp_Reader_index(lisp_Reader*, lisp_u64);
static lisp_i64 lisp_Reader_index_of(lisp_u8*, lisp_u8);

static lisp_u8 lisp_Reader_read(lisp_Reader*);
static lisp_u8 lisp_Reader_unread(lisp_Reader*);

static lisp_u64 lisp_Reader_next_whitespace(lisp_Reader*, lisp_u8);
static lisp_u8* lisp_Reader_next_token(lisp_Reader*, lisp_u8);
static lisp_u8* lisp_Reader_next_number(lisp_Reader*, lisp_u8);

static struct lisp_Value* lisp_Reader_next(lisp_Reader*, lisp_u8);

static struct lisp_Value* lisp_Reader_read_number(lisp_Reader*, lisp_u8);

static struct lisp_Value* lisp_Reader_read_list(lisp_Reader*, lisp_u8);
static struct lisp_Value* lisp_Reader_read_vector(lisp_Reader*, lisp_u8);

static struct lisp_Value* lisp_Reader_read_string(lisp_Reader*, lisp_u8);
static struct lisp_Value* lisp_Reader_read_character(lisp_Reader*, lisp_u8);

static struct lisp_Value* lisp_Reader_read_token(lisp_Reader*, lisp_u8);

static void lisp_Reader_read_comment(lisp_Reader*, lisp_u8);


#endif
