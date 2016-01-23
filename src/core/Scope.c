#ifndef __LISP_CORE_SCOPE_C__
#define __LISP_CORE_SCOPE_C__


static lisp_Scope* lisp_Scope_constructor(lisp_State* state, lisp_Scope* scope, lisp_Scope* parent) {
    scope->state = state;
    scope->map = lisp_MutMap_new();
    scope->parent = parent;
    return scope;
}

static void lisp_Scope_destructor(lisp_Scope* scope) {
    for (lisp_u64 i = 0, il = lisp_MutMap_size(scope->map); i < il; i++) {
        lisp_Value_deref(scope->state, lisp_MutList_get(scope->map->entries, i));
    }
    lisp_MutMap_delete(scope->map);
}

static lisp_Scope* lisp_Scope_new(lisp_State* state, lisp_Scope* parent) {
    return lisp_Scope_constructor(state, (lisp_Scope*) malloc(sizeof(lisp_Scope)), parent);
}

static void lisp_Scope_delete(lisp_Scope* scope) {
    lisp_Scope_destructor(scope);
    free(scope);
}

static lisp_Scope* lisp_Scope_get_scope(lisp_Scope* scope, lisp_Value* key) {
    if (lisp_MutMap_has(scope->map, key)) {
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
        return lisp_MutMap_get(key_scope->map, key);
    } else {
        return scope->state->nil;
    }
}

static void lisp_Scope_def(lisp_Scope* scope, lisp_Value* key, lisp_Value* value) {
    if (lisp_MutMap_has(scope->map, key)) {
        lisp_Value_deref(scope->state, lisp_MutMap_get(scope->map, key));
    } else {
        lisp_Value_ref(key);
    }

    lisp_Value_ref(value);
    lisp_MutMap_set(scope->map, key, value);
}

static void lisp_Scope_swap(lisp_Scope* scope, lisp_Value* key, lisp_Value* value) {
    lisp_Scope* key_scope = lisp_Scope_get_scope(scope, key);

    lisp_Value_ref(value);

    if (key_scope != NULL) {
        lisp_MutMap_set(key_scope->map, key, value);
    } else {
        lisp_Scope_def(scope, key, value);
    }
}

#endif
