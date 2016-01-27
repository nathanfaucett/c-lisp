#ifndef __LISP_LANG_STRING_H__
#define __LISP_LANG_STRING_H__


static lisp_u16 lisp_String_mask[] = {192, 224, 240};


typedef struct lisp_String {
    lisp_MutList* chars;
    lisp_u64 size;
} lisp_String;

static void lisp_String_alloc(lisp_State* state, lisp_Value* value);
static void lisp_String_dealloc(lisp_State* state, lisp_Value* value);

static void lisp_String_from_ascii(lisp_State* state, lisp_String* string, lisp_char* cstring, lisp_u64 start);
static lisp_u64 lisp_String_from_utf8(lisp_State* state, lisp_String* string, lisp_u32* cstring, lisp_u64 start);

static lisp_Value* lisp_String_new_ascii(lisp_State* state, lisp_char* cstring);
static lisp_Value* lisp_String_new_utf8(lisp_State* state, lisp_u32* cstring);

static lisp_Value* lisp_String_concat(lisp_State* state, lisp_String* a, lisp_String* b);

static lisp_bool lisp_String_equal(lisp_String* a, lisp_String* b);

static lisp_char* lisp_String_to_cstring(lisp_String* string);
static lisp_u32* lisp_String_to_utf8(lisp_String* string);


#endif
