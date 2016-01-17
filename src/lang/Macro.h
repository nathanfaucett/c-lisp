#ifndef __LISP_LANG_MACRO_H__
#define __LISP_LANG_MACRO_H__


typedef struct lisp_Macro {
    struct lisp_Value* value;
    struct lisp_Value* name;
    struct lisp_Value* params;
    struct lisp_Value* body;

    struct lisp_Value* symbol;
    lisp_function_pointer native;
} lisp_Macro;


static lisp_Macro* lisp_Macro_constructor(lisp_Macro*, struct lisp_Value*, struct lisp_Value*, struct lisp_Value*);
static void lisp_Macro_destructor(lisp_State*, lisp_Macro*);

static struct lisp_Value* lisp_Macro_call(lisp_State*, lisp_Macro*, struct lisp_Value*, lisp_Scope*);

static struct lisp_Value* lisp_Macro_to_string(lisp_State*, lisp_Macro*);
static lisp_bool lisp_Macro_equal(lisp_Macro*, lisp_Macro*);



#endif
