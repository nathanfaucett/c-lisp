#ifndef __LISP_LANG_VALUE_H__
#define __LISP_LANG_VALUE_H__


typedef struct lisp_Type {
    void (*alloc)(lisp_State*, struct lisp_Value*);
    void (*dealloc)(lisp_State*, struct lisp_Value*);
    void (*mark)(struct lisp_Value*);
} lisp_Type;


typedef struct lisp_Value {
    lisp_bool marked;
    void* data;
    struct lisp_Value* type;
    struct lisp_Value* values;
    struct lisp_Value* template;
} lisp_Value;


static lisp_Value* lisp_Value_alloc(lisp_State* state, lisp_Value* Type);
static void lisp_Value_dealloc(lisp_State* state, lisp_Value* value);
static void lisp_Value_mark(lisp_Value* value);

static lisp_Value* lisp_Value_lookup(lisp_State* state, lisp_Value* object, lisp_Value* type, lisp_Value* key);

static lisp_Value* lisp_Value_call1(lisp_State* state, lisp_Value* object, lisp_Value* key, lisp_Value* a0, lisp_Scope* scope);

static lisp_bool lisp_Value_inherits(lisp_State* state, lisp_Value* a, lisp_Value* b);

static lisp_bool lisp_Value_equal(lisp_State* state, lisp_Value* a, lisp_Value* b);


#endif
