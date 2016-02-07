#ifndef __LISP_CORE_SCOPE_C__
#define __LISP_CORE_SCOPE_C__


static lisp_Scope* lisp_Scope_alloc(lisp_State* state, lisp_Scope* parent) {
    lisp_Scope* scope = lisp_State_alloc(state, sizeof(lisp_Scope))->object;
    scope->parent = parent;
    scope->map = lisp_Map_new(state);
    return scope;
}
static void lisp_Scope_dealloc(lisp_State* state, lisp_Scope* scope) {
    lisp_State_dealloc(state, scope);
}

static lisp_Scope* lisp_Scope_get_scope(lisp_State* state, lisp_Scope* scope, lisp_Object* key) {
    if (lisp_Map_has(state, (lisp_Map*) scope->map->data, key)) {
        return scope;
    } else if (scope->parent != NULL) {
        return lisp_Scope_get_scope(state, scope->parent, key);
    } else {
        return NULL;
    }
}
static lisp_Object* lisp_Scope_get(lisp_State* state, lisp_Scope* scope, lisp_Object* key) {
    lisp_Scope* key_scope = lisp_Scope_get_scope(state, scope, key);

    if (key_scope != NULL) {
        return lisp_Map_get(state, (lisp_Map*) key_scope->map->data, key);
    } else {
        return NULL;
    }
}

static void lisp_Scope_def(lisp_State* state, lisp_Scope* scope, lisp_Object* key, lisp_Object* object) {
    scope->map = lisp_Map_set(state, (lisp_Map*) scope->map->data, key, object);
}
static void lisp_Scope_swap(lisp_State* state, lisp_Scope* scope, lisp_Object* key, lisp_Object* object) {
    lisp_Scope* key_scope = lisp_Scope_get_scope(state, scope, key);

    if (key_scope != NULL) {
        scope->map = lisp_Map_set(state, (lisp_Map*) key_scope->map->data, key, object);
    } else {
        lisp_Scope_def(state, scope, key, object);
    }
}

static void lisp_Scope_mut_def(lisp_State* state, lisp_Scope* scope, lisp_Object* key, lisp_Object* object) {
    lisp_Map_mut_set(state, (lisp_Map*) scope->map->data, key, object);
}


#endif
