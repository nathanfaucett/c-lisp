#ifndef __LISP_LANG_VALUE_H__
#define __LISP_LANG_VALUE_H__


typedef struct lisp_Value {
    lisp_bool marked;
    void* data;
    struct lisp_Value* type;   /* Type */
    struct lisp_Value* values; /* Map<Any, Any> */
} lisp_Value;

static lisp_Value* lisp_Value_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Value_dealloc(lisp_State* state, lisp_Value* value);
static void lisp_Value_mark(lisp_Value* value);

static lisp_Value* lisp_Value_find(lisp_State* state, lisp_Value* object, lisp_Value* key);

static lisp_Value* lisp_Value_apply(lisp_State* state, lisp_Value* object, lisp_Value* key, lisp_Value* args);
static lisp_Value* lisp_Value_call(lisp_State* state, lisp_Value* object, lisp_Value* key);
static lisp_Value* lisp_Value_call_arg1(lisp_State* state, lisp_Value* object, lisp_Value* key, lisp_Value* a0);

static lisp_bool lisp_Value_equal(lisp_State* state, lisp_Value* a, lisp_Value* b);


#endif
