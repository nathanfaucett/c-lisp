#ifndef __LISP_LANG_SCOPE_H__
#define __LISP_LANG_SCOPE_H__



typedef struct lisp_Scope {
    lisp_Object* parent;
    lisp_Object* map;
} lisp_Scope;


static void lisp_Scope_alloc(lisp_State* state, lisp_Object* object);
static void lisp_Scope_mark(lisp_Object* object);

static lisp_Object* lisp_Scope_new(lisp_State* state, lisp_Object* parent);

static lisp_Scope* lisp_Scope_get_scope(struct lisp_State* state, lisp_Scope* scope, struct lisp_Object* key);
static struct lisp_Object* lisp_Scope_get(struct lisp_State* state, lisp_Scope* scope, struct lisp_Object* key);

static void lisp_Scope_def(struct lisp_State* state, lisp_Scope* scope, struct lisp_Object* key, struct lisp_Object* object);
static void lisp_Scope_swap(struct lisp_State* state, lisp_Scope* scope, struct lisp_Object* key, struct lisp_Object* object);

static void lisp_Scope_mut_def(struct lisp_State* state, lisp_Scope* scope, struct lisp_Object* key, struct lisp_Object* object);


#endif
