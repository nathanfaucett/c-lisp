#ifndef __LISP_CORE_SCOPE_C__
#define __LISP_CORE_SCOPE_C__


static lisp_Scope* lisp_Scope_alloc(lisp_State* state, lisp_Scope* parent) {
    lisp_Scope* scope = lisp_State_alloc(state, sizeof(lisp_Scope));
    scope->state = state;
    scope->parent = parent;
    scope->map = lisp_Value_alloc(state, state->Map);
    return scope;
}
static void lisp_Scope_dealloc(lisp_Scope* scope) {
    lisp_State_dealloc(scope->state, scope);
}

static lisp_Scope* lisp_Scope_get_scope(lisp_Scope* scope, lisp_Value* key) {
    if (lisp_Map_has(scope->state, (lisp_Map*) scope->map->data, key)) {
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
        return lisp_Map_get(scope->state, (lisp_Map*) key_scope->map->data, key);
    } else {
        return NULL;
    }
}

static void lisp_Scope_def(lisp_Scope* scope, lisp_Value* key, lisp_Value* value) {
    scope->map = lisp_Map_set(scope->state, (lisp_Map*) scope->map->data, key, value);
}
static void lisp_Scope_swap(lisp_Scope* scope, lisp_Value* key, lisp_Value* value) {
    lisp_Scope* key_scope = lisp_Scope_get_scope(scope, key);

    if (key_scope != NULL) {
        scope->map = lisp_Map_set(scope->state, (lisp_Map*) key_scope->map->data, key, value);
    } else {
        lisp_Scope_def(scope, key, value);
    }
}

#endif
