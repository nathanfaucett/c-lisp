#ifndef __LISP_CORE_BOOTSTRAP_H__
#define __LISP_CORE_BOOTSTRAP_H__


static void lisp_bootstrap(lisp_State* state);

static void lisp_bootstrap_set_name(lisp_State* state, struct lisp_Value* type, lisp_char* name);

static struct lisp_Value* lisp_bootstrap_Type(lisp_State* state);

static struct lisp_Value* lisp_bootstrap_Any(lisp_State* state);
static struct lisp_Value* lisp_bootstrap_Nil(lisp_State* state);

static struct lisp_Value* lisp_bootstrap_Bool(lisp_State* state);
static struct lisp_Value* lisp_bootstrap_Char(lisp_State* state);
static struct lisp_Value* lisp_bootstrap_String(lisp_State* state);
static struct lisp_Value* lisp_bootstrap_Symbol(lisp_State* state);

static struct lisp_Value* lisp_bootstrap_Function(lisp_State* state);

static struct lisp_Value* lisp_bootstrap_List(lisp_State* state);
static struct lisp_Value* lisp_bootstrap_Vector(lisp_State* state);
static struct lisp_Value* lisp_bootstrap_Map(lisp_State* state);


#endif
