#ifndef __LISP_LANG_STRING_H__
#define __LISP_LANG_STRING_H__


static lisp_u16 lisp_String_mask[] = {192, 224, 240};


typedef struct lisp_String {
    lisp_MutList* chars;
    lisp_u64 size;
} lisp_String;

static void lisp_String_alloc(lisp_State* state, struct lisp_Value* value);
static void lisp_String_dealloc(lisp_State* state, struct lisp_Value* value);

static void lisp_String_from_ascii(lisp_State* state, lisp_String* string, lisp_char* cstring, lisp_u64 start);
static lisp_u64 lisp_String_from_utf8(lisp_State* state, lisp_String* string, lisp_u32* cstring, lisp_u64 start);

static lisp_char* lisp_String_to_cstring(lisp_String* string);

static struct lisp_Value* lisp_String_bootstrap(lisp_State* state);


#endif
