#ifndef __LISP_CORE_SCOPE_C__
#define __LISP_CORE_SCOPE_C__


static lisp_Scope* lisp_Scope_constructor(lisp_State* state, lisp_Scope* scope, lisp_Scope* parent) {
    scope->state = state;
    scope->map = lisp_Map_new();
    scope->parent = parent;
    return scope;
}

static void lisp_Scope_destructor(lisp_Scope* scope) {
    lisp_Map_delete(scope->map);
}

static lisp_Scope* lisp_Scope_new(lisp_State* state, lisp_Scope* parent) {
    return lisp_Scope_constructor(state, (lisp_Scope*) malloc(sizeof(lisp_Scope)), parent);
}

static void lisp_Scope_delete(lisp_Scope* scope) {
    lisp_Scope_destructor(scope);
    free(scope);
}

static lisp_Scope* lisp_Scope_get_scope(lisp_Scope* scope, lisp_Value* key) {
    if (lisp_Map_has(scope->map, key)) {
        return scope;
    } else if (scope->parent != NULL) {
        return lisp_Scope_get_scope(scope->parent, key);
    } else {
        return NULL;
    }
}

static lisp_Value* lisp_Scope_get(lisp_Scope* scope, lisp_Value* key) {
    lisp_Scope* key_scope = lisp_Scope_get_scope(scope, key);

    if (key_scope != NULL) {
        return lisp_Map_get(key_scope->map, key);
    } else {
        return scope->state->nil;
    }
}

static void lisp_Scope_def(lisp_Scope* scope, lisp_Value* key, lisp_Value* value) {
    if (lisp_Map_has(scope->map, key)) {
        lisp_Value_deref(scope->state, lisp_Map_get(scope->map, key));
    }
    lisp_Map_set(scope->map, key, value);
}

static void lisp_Scope_swap(lisp_Scope* scope, lisp_Value* key, lisp_Value* value) {
    lisp_Scope* key_scope = lisp_Scope_get_scope(scope, key);

    if (key_scope != NULL) {
        lisp_Map_set(key_scope->map, key, value);
    } else {
        lisp_Map_set(scope->map, key, value);
    }
}

#endif
