#ifndef __LISP_LANG_CHAR_H__
#define __LISP_LANG_CHAR_H__


static lisp_u16 lisp_Char_mask[] = {192, 224, 240};


typedef struct lisp_Char {
    lisp_u8 bytes[4];
    lisp_u8 size;
} lisp_Char;

static void lisp_Char_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Char_dealloc(lisp_State* state, lisp_Value* value);

static void lisp_Char_from_ascii(lisp_Char* ch, lisp_char i8);
static lisp_u64 lisp_Char_from_utf8(lisp_Char* ch, lisp_u32* cstring, lisp_u64 start);

static lisp_u32 lisp_Char_to_u32(lisp_Char* ch);
static lisp_char lisp_Char_to_char(lisp_Char* ch);


#endif
