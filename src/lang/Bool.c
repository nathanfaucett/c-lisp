#ifndef __LISP_LANG_BOOL_C__
#define __LISP_LANG_BOOL_C__


static lisp_Object* lisp_Bool_new(lisp_State* state, lisp_bool value) {
    lisp_Object* object = lisp_Object_boot_size(state, state->Bool, 1);
    LISP_SET_DATA(object, lisp_bool, value);
    return object;
}

static lisp_Object* lisp_Bool_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Object* self = lisp_Vector_get(state, (lisp_Vector*) args->data, 0);

    if (self->type == state->Bool) {
        if (LISP_GET_DATA(self, lisp_bool) != 0) {
            return lisp_String_from_ascii(state, "true");
        } else {
            return lisp_String_from_ascii(state, "false");
        }
    } else {
        return lisp_Object_to_string(state, self);
    }
}
static lisp_Object* lisp_Bool_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Vector* list = (lisp_Vector*) args->data;
    lisp_Object* self = lisp_Vector_get(state, list, 0);
    lisp_Object* other = lisp_Vector_get(state, list, 1);

    if (self->type == state->Bool && other->type == state->Bool) {
        lisp_bool abool = LISP_GET_DATA(self, lisp_bool);
        lisp_bool bbool = LISP_GET_DATA(other, lisp_bool);

        if ((abool == 0 && bbool == 0) || (abool != 0 && bbool != 0)) {
            return state->true;
        } else {
            return state->false;
        }
    } else {
        return lisp_Object_equal(state, self, other) ? state->true : state->false;
    }
}

static void lisp_Bool_boot(lisp_State* state) {
    lisp_Object* Bool = state->Bool;
    lisp_Vector* values = (lisp_Vector*) Bool->values->data;
    lisp_Map* prototype = (lisp_Map*) lisp_Vector_get(state, values, LISP_IDX_TYPE_PROTOTYPE)->data;

    lisp_Vector_mut_set(values, LISP_IDX_TYPE_NAME, lisp_String_from_ascii(state, "Bool"));

    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "to-string"), lisp_Native_new(state, lisp_Bool_export_to_string));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "equal"), lisp_Native_new(state, lisp_Bool_export_equal));
}


#endif
