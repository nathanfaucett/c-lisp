#ifndef __LISP_LANG_TYPE_H__
#define __LISP_LANG_TYPE_H__


typedef struct lisp_Type {
    lisp_Value* name;        /* Symbol */
    lisp_Value* attributes;  /* List<Symbol> */
    lisp_Value* types;       /* List<Type> */
    lisp_Value* prototype;   /* Map<Symbol, Function> */
    lisp_Value* template;    /* Map<Symbol, Type> */
    lisp_Value* super;       /* Type */
    void (*alloc)(lisp_State*, lisp_Value*);
    void (*dealloc)(lisp_State*, lisp_Value*);
} lisp_Type;

static void lisp_Type_constructor(
    lisp_Type* type,
    lisp_Value* name,
    lisp_Value* attributes,
    lisp_Value* types,
    lisp_Value* prototype,
    lisp_Value* template,
    lisp_Value* super,
    void (*alloc)(lisp_State*, lisp_Value*),
    void (*dealloc)(lisp_State*, lisp_Value*)
);

static lisp_bool lisp_Type_inherits(lisp_Value* child, lisp_Value* parent);

static void lisp_Type_alloc(struct lisp_State* state, lisp_Value* value);
static void lisp_Type_dealloc(struct lisp_State* state, lisp_Value* value);


#endif
