#ifndef __LISP_CORE_SCOPE_H__
#define __LISP_CORE_SCOPE_H__


typedef struct lisp_Scope {
    struct lisp_State* state;
    lisp_MutMap* map;
    struct lisp_Scope* parent;
} lisp_Scope;


static lisp_Scope* lisp_Scope_constructor(struct lisp_State*, lisp_Scope*, lisp_Scope*);
static void lisp_Scope_destructor(lisp_Scope*);

static lisp_Scope* lisp_Scope_new(struct lisp_State*, lisp_Scope*);
static void lisp_Scope_delete(lisp_Scope*);


static lisp_Scope* lisp_Scope_get_scope(lisp_Scope*, struct lisp_Value*);
static struct lisp_Value* lisp_Scope_get(lisp_Scope*, struct lisp_Value*);

static void lisp_Scope_def(lisp_Scope*, struct lisp_Value*, struct lisp_Value*);
static void lisp_Scope_swap(lisp_Scope*, struct lisp_Value*, struct lisp_Value*);


#endif
