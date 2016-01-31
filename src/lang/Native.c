#ifndef __LISP_LANG_NATIVE_C__
#define __LISP_LANG_NATIVE_C__


static void lisp_Native_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Native* native = (lisp_Native*) value->data;
    native->name = NULL;
    native->function = NULL;
}
static void lisp_Native_mark(lisp_Value* value) {
    lisp_Native* native = (lisp_Native*) value->data;

    if (native->name != NULL) {
        lisp_Value_mark(native->name);
    }
}

static lisp_Value* lisp_Native_new(lisp_State* state, lisp_Value* name, lisp_Value* (*function)(lisp_State*, lisp_Value*, lisp_Scope* scope)) {
    lisp_Value* value = lisp_Value_alloc(state, state->Native);
    lisp_Native* native = (lisp_Native*) value->data;

    native->name = name;
    native->function = function;

    return value;
}

static lisp_Value* lisp_Native_call(lisp_State* state, lisp_Native* native, lisp_Value* args, lisp_Scope* scope) {
    return native->function(state, args, scope);
}


#endif
