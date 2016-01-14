#ifndef __LISP_LANG_VALUE_H__
#define __LISP_LANG_VALUE_H__


typedef enum LISP_TYPE {
    LISP_TYPE_CHARACTER,
    LISP_TYPE_NIL,
    LISP_TYPE_NUMBER,
    LISP_TYPE_STRING,
    LISP_TYPE_SYMBOL,
    LISP_TYPE_LIST,
    LISP_TYPE_VECTOR
} LISP_TYPE;


typedef struct lisp_Value {
    LISP_TYPE type;
    lisp_u32 ref_count;
    union {
        struct lisp_Character character;
        struct lisp_List list;
        struct lisp_Nil nil;
        struct lisp_Number number;
        struct lisp_String string;
        struct lisp_Symbol symbol;
        struct lisp_Vector vector;
    };
} lisp_Value;


static struct lisp_Value* lisp_Value_constructor(lisp_Value*, LISP_TYPE);
static void lisp_Value_destructor(lisp_State*, lisp_Value*);

static struct lisp_Value* lisp_Value_new(lisp_State*, LISP_TYPE);
static void lisp_Value_delete(lisp_State*, lisp_Value*);

static lisp_Value* lisp_Value_character_from_ch(lisp_State*, lisp_u8);
static lisp_Value* lisp_Value_string_from_cstring(lisp_State*, lisp_u8*);
static lisp_Value* lisp_Value_symbol_from_cstring(lisp_State*, lisp_u8*);
static lisp_Value* lisp_Value_number_from_i32(lisp_State*, lisp_i32);
static lisp_Value* lisp_Value_number_from_f64(lisp_State*, lisp_f64);

static lisp_Value* lisp_Value_list_from_array(lisp_State*, lisp_Array*);
static lisp_Value* lisp_Value_list_from_vector(lisp_State*, lisp_Array*);

static lisp_Value* lisp_Value_nil(lisp_State*);
static lisp_Value* lisp_Value_list(lisp_State*);
static lisp_Value* lisp_Value_vector(lisp_State*);

static lisp_Value* lisp_Value_new_nil(lisp_State*);
static lisp_Value* lisp_Value_new_list(lisp_State*);
static lisp_Value* lisp_Value_new_vector(lisp_State*);

static void lisp_Value_ref(lisp_Value*);
static void lisp_Value_deref(lisp_State*, lisp_Value*);

static lisp_Value* lisp_Value_to_string(lisp_State*, lisp_Value*);


#endif
