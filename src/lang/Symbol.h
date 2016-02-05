#ifndef __LISP_LANG_SYMBOL_H__
#define __LISP_LANG_SYMBOL_H__


typedef struct lisp_Symbol {
    lisp_Object* value;
} lisp_Symbol;


static void lisp_Symbol_alloc(lisp_State* state, lisp_Object* object);
static void lisp_Symbol_mark(lisp_Object* object);

static lisp_Object* lisp_Symbol_from_ascii(lisp_State* state, lisp_char* ascii);

static lisp_Object* lisp_Symbol_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope);
static lisp_Object* lisp_Symbol_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope);

static void lisp_Symbol_boot(lisp_State* state);


#endif
