#ifndef __LISP_LANG_NATIVE_C__
#define __LISP_LANG_NATIVE_C__


static lisp_Object* lisp_Native_new(lisp_State* state, lisp_Object* (*fn)(lisp_State*, lisp_Object*, lisp_Object*)) {
    lisp_Object* object = lisp_Object_boot_alloc(state, state->Native);
    object->data = fn;
    return object;
}

static lisp_Object* lisp_Native_call(lisp_State* state, lisp_Object* native, lisp_Object* args, lisp_Object* scope) {
    lisp_Object* (*fn)(lisp_State*, lisp_Object*, lisp_Object*) = native->data;
    return fn(state, args, scope);
}

static lisp_Object* lisp_Native_export_call(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Object* get = lisp_Symbol_from_ascii(state, "get");
    lisp_Object* self = lisp_Object_call1(state, args, get, lisp_Number_UInt(state, 0), scope);
    lisp_Object* fn_args = lisp_Object_call1(state, args, get, lisp_Number_UInt(state, 1), scope);

    if (self->type == state->Native && lisp_Object_inherits(state, fn_args->type, state->Indexed)) {
        return lisp_Native_call(state, self, fn_args, scope);
    } else {
        /* throw error */
        return state->nil;
    }
}
static lisp_Object* lisp_Native_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    return lisp_String_from_ascii(state, "NativeFunction");
}
static lisp_Object* lisp_Native_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Object* get = lisp_Symbol_from_ascii(state, "get");
    lisp_Object* self = lisp_Object_call1(state, args, get, lisp_Number_UInt(state, 0), scope);
    lisp_Object* other = lisp_Object_call1(state, args, get, lisp_Number_UInt(state, 1), scope);

    if (LISP_GET_DATA(self, lisp_bool) == LISP_GET_DATA(other, lisp_bool)) {
        return state->true;
    } else {
        return state->false;
    }
}

static void lisp_Native_boot(lisp_State* state) {
    lisp_Object* Native = state->Native;
    lisp_List* values = (lisp_List*) Native->values->data;
    lisp_Map* prototype = (lisp_Map*) lisp_List_get(state, values, LISP_IDX_TYPE_PROTOTYPE)->data;

    lisp_List_mut_set(values, LISP_IDX_TYPE_NAME, lisp_String_from_ascii(state, "Native"));

    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "call"), lisp_Native_new(state, lisp_Native_export_call));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "to-string"), lisp_Native_new(state, lisp_Native_export_to_string));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "equal"), lisp_Native_new(state, lisp_Native_export_equal));
}


#endif
