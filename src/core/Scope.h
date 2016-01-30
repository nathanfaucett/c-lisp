#ifndef __LISP_CORE_SCOPE_H__
#define __LISP_CORE_SCOPE_H__


typedef struct lisp_Scope {
    struct lisp_State* state;
    struct lisp_Scope* parent;
    struct lisp_Value* map;
} lisp_Scope;


static lisp_Scope* lisp_Scope_alloc(struct lisp_State* state, lisp_Scope*);
static void lisp_Scope_dealloc(lisp_Scope*);

static lisp_Scope* lisp_Scope_get_scope(lisp_Scope* scope, struct lisp_Value* key);
static struct lisp_Value* lisp_Scope_get(lisp_Scope* scope, struct lisp_Value* key);

static void lisp_Scope_def(lisp_Scope* scope, struct lisp_Value* key, struct lisp_Value* value);
static void lisp_Scope_swap(lisp_Scope* scope, struct lisp_Value* key, struct lisp_Value* value);


#endif
