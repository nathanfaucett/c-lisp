#ifndef __LISP_LANG_SYMBOL_H__
#define __LISP_LANG_SYMBOL_H__


typedef struct lisp_Symbol {
    lisp_Value* string;
} lisp_Symbol;


static void lisp_Symbol_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Symbol_mark(lisp_Value* value);

static lisp_Value* lisp_Symbol_new_ascii(lisp_State* state, lisp_char* ascii);

static lisp_bool lisp_Symbol_equal(lisp_Symbol* a, lisp_Symbol* b);

static lisp_Value* lisp_export_Symbol_constructor(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_export_Symbol_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope);
static lisp_Value* lisp_export_Symbol_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope);

static void lisp_Symbol_boot(lisp_State* state);


#endif
