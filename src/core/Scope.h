#ifndef __LISP_CORE_SCOPE_H__
#define __LISP_CORE_SCOPE_H__



typedef struct lisp_Scope {
    struct lisp_Scope* parent;
    struct lisp_Object* map;
} lisp_Scope;


static lisp_Scope* lisp_Scope_alloc(struct lisp_State* state, lisp_Scope* parent);
static void lisp_Scope_dealloc(struct lisp_State* state, lisp_Scope*);

static lisp_Scope* lisp_Scope_get_scope(struct lisp_State* state, lisp_Scope* scope, struct lisp_Object* key);
static struct lisp_Object* lisp_Scope_get(struct lisp_State* state, lisp_Scope* scope, struct lisp_Object* key);

static void lisp_Scope_def(struct lisp_State* state, lisp_Scope* scope, struct lisp_Object* key, struct lisp_Object* object);
static void lisp_Scope_swap(struct lisp_State* state, lisp_Scope* scope, struct lisp_Object* key, struct lisp_Object* object);

static void lisp_Scope_mut_def(struct lisp_State* state, lisp_Scope* scope, struct lisp_Object* key, struct lisp_Object* object);


#endif
