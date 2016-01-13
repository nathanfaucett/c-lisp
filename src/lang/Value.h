#ifndef __LISP_LANG_VALUE_H__
#define __LISP_LANG_VALUE_H__


typedef enum LISP_TYPE {
    LISP_TYPE_CHARACTER,
    LISP_TYPE_NIL,
    LISP_TYPE_NUMBER,
    LISP_TYPE_STRING,
    LISP_TYPE_LIST
} LISP_TYPE;


typedef struct lisp_Value {
    LISP_TYPE type;
    lisp_u32 ref_count;
    union {
        struct lisp_Character character;
        struct lisp_Nil nil;
        struct lisp_Number number;
        struct lisp_String string;
        struct lisp_List list;
    };
} lisp_Value;


inline static lisp_Value* lisp_Value_ch(lisp_State*, lisp_u8);
inline static lisp_Value* lisp_Value_cstring(lisp_State*, lisp_u8*);
inline static lisp_Value* lisp_Value_nil(lisp_State*);
inline static lisp_Value* lisp_Value_number(lisp_State*, lisp_f64);
inline static lisp_Value* lisp_Value_list(lisp_State*);

inline static void lisp_Value_delete(lisp_State*, lisp_Value*);

inline static void lisp_Value_ref(lisp_Value*);
inline static void lisp_Value_deref(lisp_State*, lisp_Value*);

inline static lisp_u8* lisp_Value_to_cstring(lisp_Value*);


#endif
