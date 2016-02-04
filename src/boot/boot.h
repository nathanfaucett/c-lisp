#ifndef __LISP_BOOT_H__
#define __LISP_BOOT_H__


#define LISP_IDX_TYPE_NAME 0
#define LISP_IDX_TYPE_ATTRIBUTES 1
#define LISP_IDX_TYPE_TYPES 2
#define LISP_IDX_TYPE_SIZE 3
#define LISP_IDX_TYPE_SUPER 4
#define LISP_IDX_TYPE_PROTOTYPE 5
#define LISP_IDX_TYPE_TEMPLATE 6
#define LISP_IDX_TYPE_ABSTRACT 7
#define LISP_IDX_TYPE_BYTES 8
#define LISP_TYPE_SIZE 9


#define LISP_SET_DATA(object, type, value) \
    *((type*) object->data) = value
#define LISP_GET_DATA(object, type) \
    *((type*) object->data)


static void lisp_boot(lisp_State* state);

static void lisp_boot_MainType(lisp_State* state);
static void lisp_boot_Type (
    lisp_State* state,
    lisp_Value* value,
    lisp_Value* super,
    lisp_size size,
    lisp_size values_size,
    lisp_bool abstract,
    lisp_bool bytes,
    void (*alloc)(lisp_State*, lisp_Value*),
    void (*dealloc)(lisp_State*, lisp_Value*),
    void (*mark)(lisp_Value*)
);

static lisp_Value* lisp_boot_new_value(lisp_State* state, lisp_Value* type);
static lisp_Value* lisp_boot_new_size(lisp_State* state, lisp_Value* type, lisp_size size);
static lisp_Value* lisp_boot_new_data(lisp_State* state, lisp_Value* type, void* data);

static lisp_Value* lisp_boot_new_mutablelist(lisp_State* state);
static lisp_Value* lisp_boot_new_mutablemap(lisp_State* state);

static lisp_Value* lisp_boot_new_list(lisp_State* state);
static lisp_Value* lisp_boot_new_list_node(lisp_State* state);
static lisp_Value* lisp_boot_new_map(lisp_State* state);

#endif
