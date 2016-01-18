#ifndef __LISP_CORE_SPECIAL_FORMS_H__
#define __LISP_CORE_SPECIAL_FORMS_H__


static struct lisp_Value* lisp_special_form_quote(struct lisp_State*, struct lisp_Value*, lisp_Scope*);
static struct lisp_Value* lisp_special_form_def(struct lisp_State*, struct lisp_Value*, lisp_Scope*);
static struct lisp_Value* lisp_special_form_swap(struct lisp_State*, struct lisp_Value*, lisp_Scope*);
static struct lisp_Value* lisp_special_form_if(struct lisp_State*, struct lisp_Value*, lisp_Scope*);
static struct lisp_Value* lisp_special_form_fn(struct lisp_State*, struct lisp_Value*, lisp_Scope*);
static struct lisp_Value* lisp_special_form_macro(struct lisp_State*, struct lisp_Value*, lisp_Scope*);
static struct lisp_Value* lisp_special_form_do(struct lisp_State*, struct lisp_Value*, lisp_Scope*);
static struct lisp_Value* lisp_special_form_let(struct lisp_State*, struct lisp_Value*, lisp_Scope*);
static struct lisp_Value* lisp_special_form_eval(struct lisp_State*, struct lisp_Value*, lisp_Scope*);


#endif
