#ifndef __LISP_LANG_TYPE_H__
#define __LISP_LANG_TYPE_H__


typedef struct lisp_Type {
    struct lisp_Value* name;
    struct lisp_Value* parameters;
    struct lisp_Value* types;
    struct lisp_Value* methods;
    struct lisp_Value* super;
    void (*alloc)(lisp_State*, struct lisp_Value*);
    void (*dealloc)(lisp_State*, struct lisp_Value*);
} lisp_Type;

static void lisp_Type_constructor(
    lisp_Type* type,
    struct lisp_Value* name,
    struct lisp_Value* parameters,
    struct lisp_Value* types,
    struct lisp_Value* methods,
    struct lisp_Value* super,
    void (*alloc)(lisp_State*, struct lisp_Value*),
    void (*dealloc)(lisp_State*, struct lisp_Value*)
);

static void lisp_Type_default_alloc(struct lisp_State* state, struct lisp_Value* value);
static void lisp_Type_default_dealloc(struct lisp_State* state, struct lisp_Value* value);

static void lisp_Type_alloc(struct lisp_State* state, struct lisp_Value* value);
static void lisp_Type_dealloc(struct lisp_State* state, struct lisp_Value* value);

static struct lisp_Value* lisp_Type_bootstrap(lisp_State* state);


#endif
