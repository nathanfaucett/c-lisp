#ifndef __LISP_LANG_TYPE_H__
#define __LISP_LANG_TYPE_H__


typedef struct lisp_Type {
    lisp_size size;

    lisp_Value* name;        /* Symbol */
    lisp_Value* attributes;  /* Seq<Symbol> */
    lisp_Value* types;       /* Seq<Type> */
    lisp_Value* prototype;   /* Map<Symbol, Callable> */
    lisp_Value* template;    /* Map<Symbol, Type> */
    lisp_Value* super;       /* Type */
    lisp_Value* abstract;    /* Bool */
    lisp_Value* bytes;        /* Bool */

    void (*alloc)(lisp_State*, lisp_Value*);
    void (*dealloc)(lisp_State*, lisp_Value*);
    void (*mark)(lisp_Value*);
} lisp_Type;


#endif
