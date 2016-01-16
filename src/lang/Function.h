#ifndef __LISP_LANG_FUNCTION_H__
#define __LISP_LANG_FUNCTION_H__


typedef struct lisp_Function {
    struct lisp_Value* value;
    struct lisp_Value* name;
    struct lisp_Value* params;
    struct lisp_Value* body;
} lisp_Function;


static lisp_Function* lisp_Function_constructor(lisp_Function*, struct lisp_Value*, struct lisp_Value*, struct lisp_Value*);
static void lisp_Function_destructor(lisp_State*, lisp_Function*);

static struct lisp_Value* lisp_Function_call(lisp_State*, lisp_Function*, struct lisp_Value*, lisp_Scope*);

static struct lisp_Value* lisp_Function_to_string(lisp_State*, lisp_Function*);
static lisp_bool lisp_Function_equal(lisp_Function*, lisp_Function*);



#endif
