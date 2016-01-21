#ifndef __LISP_LANG_TYPE_H__
#define __LISP_LANG_TYPE_H__


typedef struct lisp_Type {
    struct lisp_Value* name;
    struct lisp_Value* parameters;
    struct lisp_Value* types;
    struct lisp_Value* methods;
    struct lisp_Type* super;
    void (*alloc)(lisp_State*, struct lisp_Value*);
    void (*dealloc)(lisp_State*, struct lisp_Value*);
} lisp_Type;

static void lisp_Type_constructor(
    lisp_Type* type,
    struct lisp_Value* name,
    struct lisp_Value* parameters,
    struct lisp_Value* types,
    struct lisp_Value* methods,
    lisp_Type* super,
    void (*alloc)(lisp_State*, struct lisp_Value*),
    void (*dealloc)(lisp_State*, struct lisp_Value*)
);

static void lisp_Type_alloc(struct lisp_State* state, struct lisp_Value* value);
static void lisp_Type_dealloc(struct lisp_State* state, struct lisp_Value* value);

lisp_bool lisp_Type_is(struct lisp_Value* value, lisp_Type* type);


#endif
