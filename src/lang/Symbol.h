#ifndef __LISP_LANG_SYMBOL_H__
#define __LISP_LANG_SYMBOL_H__


typedef struct lisp_Symbol {
    lisp_Value* value;
} lisp_Symbol;

static void lisp_Symbol_alloc(lisp_State* state, struct lisp_Value* value);
static void lisp_Symbol_dealloc(lisp_State* state, struct lisp_Value* value);

static void lisp_Symbol_from_ascii(lisp_State* state, lisp_Symbol* symbol, lisp_char* cstring, lisp_u64 start);
static lisp_u64 lisp_Symbol_from_utf8(lisp_State* state, lisp_Symbol* symbol, lisp_u32* cstring, lisp_u64 start);


#endif
