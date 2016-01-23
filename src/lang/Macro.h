#ifndef __LISP_LANG_MACRO_H__
#define __LISP_LANG_MACRO_H__


typedef struct lisp_Macro {
    struct lisp_Value* value;

    struct lisp_Value* name;
    struct lisp_Value* params;
    struct lisp_Value* body;

    struct lisp_Value* (*native)(lisp_State*, struct lisp_Value*, struct lisp_Scope*);
} lisp_Macro;


static void lisp_Macro_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Macro_dealloc(lisp_State* state, lisp_Value* value);

static struct lisp_Value* lisp_Macro_call(lisp_State*, lisp_Macro*, struct lisp_Value*, lisp_Scope*);



#endif
