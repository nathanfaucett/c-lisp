#ifndef __LISP_LANG_VALUE_H__
#define __LISP_LANG_VALUE_H__


typedef struct lisp_Value {
    lisp_bool marked;
    void* data;
    struct lisp_Value* type;   /* Type */
    struct lisp_Value* values; /* List<Any> */
} lisp_Value;

static lisp_Value* lisp_Value_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Value_dealloc(lisp_State* state, lisp_Value* value);
static void lisp_Value_mark(lisp_Value* value);

static lisp_Value* lisp_Value_find(lisp_State* state, lisp_Value* object, lisp_Value* key);

static lisp_bool lisp_Value_equal(lisp_State* state, lisp_Value* a, lisp_Value* b);
static lisp_Value* lisp_Value_to_string(lisp_State* state, lisp_Value* value);


#endif
