#ifndef __LISP_LANG_SCOPE_C__
#define __LISP_LANG_SCOPE_C__


static void lisp_Scope_alloc(lisp_State* state, lisp_Object* object) {
    lisp_Scope* scope = (lisp_Scope*) object->data;
    scope->parent = NULL;
    scope->map = NULL;
}
static void lisp_Scope_mark(lisp_Object* object) {
    lisp_Scope* scope = (lisp_Scope*) object->data;

    if (scope->parent != NULL) {
        lisp_Object_mark(scope->parent);
    }
    if (scope->map != NULL) {
        lisp_Object_mark(scope->map);
    }
}

static lisp_Object* lisp_Scope_new(lisp_State* state, lisp_Object* parent) {
    lisp_Object* object = lisp_Object_boot_size(state, state->List, sizeof(lisp_List));
    lisp_Scope* scope = (lisp_Scope*) object->data;
    scope->parent = parent;
    scope->map = NULL;
    return object;
}

static lisp_Scope* lisp_Scope_get_scope(lisp_State* state, lisp_Scope* scope, lisp_Object* key) {
    if (scope->map != NULL) {
        if (lisp_Map_has(state, (lisp_Map*) scope->map->data, key)) {
            return scope;
        } else if (scope->parent != NULL) {
            return lisp_Scope_get_scope(state, (lisp_Scope*) scope->parent->data, key);
        } else {
            return NULL;
        }
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
    if (scope->map == NULL) {
        scope->map = lisp_Map_new(state);
    }
    scope->map = lisp_Map_set(state, (lisp_Map*) scope->map->data, key, object);
}
static void lisp_Scope_swap(lisp_State* state, lisp_Scope* scope, lisp_Object* key, lisp_Object* object) {
    lisp_Scope* key_scope = lisp_Scope_get_scope(state, scope, key);

    if (key_scope != NULL) {
        if (scope->map == NULL) {
            scope->map = lisp_Map_new(state);
        }
        scope->map = lisp_Map_set(state, (lisp_Map*) key_scope->map->data, key, object);
    } else {
        lisp_Scope_def(state, scope, key, object);
    }
}

static void lisp_Scope_mut_def(lisp_State* state, lisp_Scope* scope, lisp_Object* key, lisp_Object* object) {
    if (scope->map == NULL) {
        scope->map = lisp_Map_new(state);
    }
    lisp_Map_mut_set(state, (lisp_Map*) scope->map->data, key, object);
}


#endif
