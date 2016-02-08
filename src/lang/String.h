#ifndef __LISP_LANG_STRING_H__
#define __LISP_LANG_STRING_H__


typedef struct lisp_String {
    lisp_Object** chars;
    lisp_size size;
} lisp_String;


static void lisp_String_alloc(lisp_State* state, lisp_Object* object);
static void lisp_String_mark(lisp_Object* object);

static lisp_Object* lisp_String_from_ascii(lisp_State* state, lisp_char* ascii);
static lisp_char* lisp_String_to_ascii(lisp_String* string);
static lisp_bool lisp_String_equal(lisp_String* a, lisp_String* b);

static lisp_Object* lisp_String_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope);
static lisp_Object* lisp_String_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope);

static void lisp_String_boot(lisp_State* state);


#endif
