#ifndef __LISP_LANG_STRING_H__
#define __LISP_LANG_STRING_H__


typedef struct lisp_String {
    struct lisp_Value* value;
    lisp_Character** chars;
    lisp_u32 size;
} lisp_String;


inline static lisp_String* lisp_String_cstring(lisp_State*, lisp_String*, lisp_u8*);
inline static void lisp_String_delete(lisp_State*, lisp_String*);

inline static lisp_u8* lisp_String_to_cstring(lisp_String*);


#endif
