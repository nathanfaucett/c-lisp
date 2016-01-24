#ifndef __LISP_CORE_READER_H__
#define __LISP_CORE_READER_H__


struct FILE;
int getc(FILE* fp);
int fseek(FILE* stream, long offset, int whence);

#ifndef SEEK_CUR
#define SEEK_CUR 0
#endif

#ifndef EOF
#define EOF -1
#endif


typedef struct lisp_Reader {
    struct lisp_State* state;
    FILE* file;
    lisp_char* cstring;
    lisp_u64 index;
    lisp_u64 column;
    lisp_u64 row;
} lisp_Reader;


static lisp_Reader* lisp_Reader_constructor(lisp_Reader* reader, struct lisp_State* state, lisp_char*, FILE* file);

static lisp_Reader* lisp_Reader_from_cstring(struct lisp_State* state, lisp_char*);
static lisp_Reader* lisp_Reader_from_file(struct lisp_State* state, FILE*);
static void lisp_Reader_delete(lisp_Reader* reader);

static lisp_bool lisp_Reader_is_marco(lisp_u32 ch);

static lisp_u32 lisp_Reader_index(lisp_Reader* reader, lisp_u64 index);

static lisp_u32 lisp_Reader_read(lisp_Reader* reader);
static lisp_u32 lisp_Reader_unread(lisp_Reader* reader);

static lisp_u64 lisp_Reader_next_whitespace(lisp_Reader* reader, lisp_u32 ch);
static lisp_u32* lisp_Reader_next_token(lisp_Reader* reader, lisp_u32 ch);
static lisp_char* lisp_Reader_next_number(lisp_Reader* reader, lisp_u32 ch);

static struct lisp_Value* lisp_Reader_next(lisp_Reader* reader, lisp_u32 ch);

static struct lisp_Value* lisp_Reader_read_number(lisp_Reader* reader, lisp_u32 ch);

static struct lisp_Value* lisp_Reader_read_list(lisp_Reader* reader, lisp_u32 ch);
static struct lisp_Value* lisp_Reader_read_vector(lisp_Reader* reader, lisp_u32 ch);
static struct lisp_Value* lisp_Reader_read_map(lisp_Reader* reader, lisp_u32 ch);

static struct lisp_Value* lisp_Reader_read_string(lisp_Reader* reader, lisp_u32 ch);
static struct lisp_Value* lisp_Reader_read_character(lisp_Reader* reader, lisp_u32 ch);

static struct lisp_Value* lisp_Reader_read_token(lisp_Reader* reader, lisp_u32 ch);

static void lisp_Reader_read_comment(lisp_Reader* reader, lisp_u32 ch);


#endif
