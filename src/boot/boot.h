#ifndef __LISP_BOOT_H__
#define __LISP_BOOT_H__


#define LISP_SET_DATA(Value, type, value) \
    *((type*) Value->data) = value;


static void lisp_boot(lisp_State* state);

static lisp_Value* lisp_boot_create_MainType(lisp_State* state);

static lisp_Value* lisp_boot_create_BootType(
    lisp_State* state,
    lisp_Value* super,
    lisp_size size,
    void (*alloc)(lisp_State*, lisp_Value*),
    void (*dealloc)(lisp_State*, lisp_Value*),
    void (*mark)(lisp_Value*)
);

static void lisp_boot_create_InitType(
    lisp_State* state,
    lisp_Value* value,
    lisp_char* ascii,
    lisp_bool abstract,
    lisp_bool bytes
);

static lisp_Value* lisp_boot_create_Type(
    lisp_State* state,
    lisp_Value* super,
    lisp_size size,
    lisp_char* ascii,
    void (*alloc)(lisp_State*, lisp_Value*),
    void (*dealloc)(lisp_State*, lisp_Value*),
    void (*mark)(lisp_Value*)
);
static lisp_Value* lisp_boot_create_AbstractType(lisp_State* state, lisp_Value* super, lisp_char* ascii);
static lisp_Value* lisp_boot_create_BytesType(lisp_State* state, lisp_Value* super, lisp_size size, lisp_char* ascii);

#endif
