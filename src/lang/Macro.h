#ifndef __LISP_LANG_MACRO_H__
#define __LISP_LANG_MACRO_H__


typedef struct lisp_Macro {
    lisp_Value* value;

    lisp_Value* name;
    lisp_Value* params;
    lisp_Value* body;

    lisp_Value* (*native)(lisp_State*, lisp_Value*, struct lisp_Scope*);
} lisp_Macro;


static void lisp_Macro_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Macro_dealloc(lisp_State* state, lisp_Value* value);

static lisp_Value* lisp_Macro_call(lisp_State*, lisp_Macro*, lisp_Value*, lisp_Scope*);



#endif
