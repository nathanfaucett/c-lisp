#ifndef __LISP_LANG_CHARACER_H__
#define __LISP_LANG_CHARACER_H__


typedef struct lisp_Character {
    struct lisp_Value* value;
    lisp_u8* bytes;
    lisp_u8 size;

} lisp_Character;


inline static lisp_Character* lisp_Character_u8(lisp_Character*, lisp_u8);
inline static lisp_Character* lisp_Character_bytes(lisp_Character*, lisp_u8*, lisp_u8);

inline static void lisp_Character_delete(lisp_Character*);

inline static lisp_u8 lisp_Character_to_char(lisp_Character*);


#endif
