#ifndef __LISP_CORE_BOOTSTRAP_H__
#define __LISP_CORE_BOOTSTRAP_H__


static void lisp_bootstrap(struct lisp_State* state);

static struct lisp_Value* lisp_bootstrap_Type(struct lisp_State* state);
static struct lisp_Value* lisp_bootstrap_SubType(
    struct lisp_State* state,
    struct lisp_Value* parent,
    void (*alloc)(struct lisp_State*, struct lisp_Value*),
    void (*dealloc)(struct lisp_State*, struct lisp_Value*)
);

static void lisp_bootstrap_defmethod(
    struct lisp_State* state,
    lisp_MutList* mut_list,
    lisp_char* cstring,
    struct lisp_Value* (*native)(struct lisp_State*, struct lisp_Value*, struct lisp_Scope*)
);


#endif
