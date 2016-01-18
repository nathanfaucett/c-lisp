#ifndef __LISP_LANG_STRING_H__
#define __LISP_LANG_STRING_H__


typedef struct lisp_String {
    struct lisp_Value* value;
    lisp_Character** chars;
    lisp_u32 size;
} lisp_String;


static void lisp_String_destructor(lisp_State*, lisp_String*);

static lisp_String* lisp_String_from_cstring(lisp_State*, lisp_String*, lisp_u8*);
static lisp_String* lisp_String_from_mut_list(lisp_State*, lisp_String*, lisp_MutList*);

static struct lisp_Value* lisp_String_concat(lisp_State*, lisp_String*, lisp_String*);

static lisp_u8* lisp_String_to_cstring(lisp_String*);

static lisp_bool lisp_String_equal(lisp_String*, lisp_String*);


#endif
