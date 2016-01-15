#ifndef __LISP_LANG_CHARACER_H__
#define __LISP_LANG_CHARACER_H__


typedef struct lisp_Character {
    struct lisp_Value* value;
    lisp_u8* bytes;
    lisp_u8 size;
} lisp_Character;


static lisp_Character* lisp_Character_from_u8(lisp_Character*, lisp_u8);
static lisp_Character* lisp_Character_from_bytes(lisp_Character*, lisp_u8*, lisp_u8);

static void lisp_Character_destructor(lisp_Character*);

static lisp_u8 lisp_Character_to_char(lisp_Character*);
static struct lisp_Value* lisp_Character_to_string(lisp_State*, lisp_Character*);

static lisp_bool lisp_Character_equal(lisp_Character*, lisp_Character*);


#endif
