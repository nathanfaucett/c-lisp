#ifndef __LISP_LANG_MACRO_H__
#define __LISP_LANG_MACRO_H__


typedef struct lisp_Macro {
    lisp_Value* name;
    lisp_Value* dispatches;
} lisp_Macro;


static void lisp_Macro_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Macro_mark(lisp_Value* value);

static lisp_Value* lisp_Macro_call(lisp_State* state, lisp_Macro* macro, lisp_Value* args, lisp_Scope* scope);


#endif
