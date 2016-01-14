#ifndef __LISP_LANG_SYMBOL_H__
#define __LISP_LANG_SYMBOL_H__


typedef struct lisp_Symbol {
    struct lisp_Value* value;
    struct lisp_Value* string;
} lisp_Symbol;

static void lisp_Symbol_destructor(lisp_State*, lisp_Symbol*);

static struct lisp_Symbol* lisp_Symbol_from_cstring(lisp_State*, lisp_Symbol*, lisp_u8*);

static struct lisp_Value* lisp_Symbol_to_string(lisp_State*, lisp_Symbol*);


#endif
