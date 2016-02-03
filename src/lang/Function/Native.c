#ifndef __LISP_LANG_NATIVE_C__
#define __LISP_LANG_NATIVE_C__


static lisp_Value* lisp_Native_new(lisp_State* state, lisp_Value* (*fn)(lisp_State*, lisp_Value*, lisp_Scope*)) {
    lisp_Value* value = lisp_boot_new_value(state, state->Native);
    value->data = fn;
    return value;
}

static lisp_Value* lisp_Native_call(lisp_State* state, lisp_Value* native, lisp_Value* args, lisp_Scope* scope) {
    lisp_Value* (*fn)(lisp_State*, lisp_Value*, lisp_Scope*) = native->data;
    return fn(state, args, scope);
}

static lisp_Value* lisp_Native_export_call(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    lisp_Value* get = lisp_Symbol_from_ascii(state, "get");
    lisp_Value* self = lisp_Value_call1(state, args, get, lisp_Number_UInt(state, 0), scope);
    lisp_Value* fn_args = lisp_Value_call1(state, args, get, lisp_Number_UInt(state, 1), scope);

    if (self->type == state->Native && lisp_Value_inherits(state, fn_args->type, state->Indexed)) {
        return lisp_Native_call(state, self, fn_args, scope);
    } else {
        /* throw error */
        return state->nil;
    }
}
static lisp_Value* lisp_Native_export_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return lisp_String_from_ascii(state, "NativeFunction");
}
static lisp_Value* lisp_Native_export_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    lisp_Value* get = lisp_Symbol_from_ascii(state, "get");
    lisp_Value* self = lisp_Value_call1(state, args, get, lisp_Number_UInt(state, 0), scope);
    lisp_Value* other = lisp_Value_call1(state, args, get, lisp_Number_UInt(state, 1), scope);

    if (self->data == other->data) {
        return state->true;
    } else {
        return state->false;
    }
}

static void lisp_Native_boot(lisp_State* state) {
    lisp_Value* Native = state->Native;
    lisp_Map* prototype = (lisp_Map*) lisp_Array_get(state, (lisp_Array*) Native->values->data, LISP_IDX_TYPE_PROTOTYPE)->data;

    lisp_Map_set(state, prototype, lisp_Symbol_from_ascii(state, "call"), lisp_Native_new(state, lisp_Native_export_call));
    lisp_Map_set(state, prototype, lisp_Symbol_from_ascii(state, "to-string"), lisp_Native_new(state, lisp_Native_export_to_string));
    lisp_Map_set(state, prototype, lisp_Symbol_from_ascii(state, "equal"), lisp_Native_new(state, lisp_Native_export_equal));
}


#endif
