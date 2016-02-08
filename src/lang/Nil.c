#ifndef __LISP_LANG_NIL_C__
#define __LISP_LANG_NIL_C__


static lisp_Object* lisp_Nil_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_Object* self = lisp_List_get(state, (lisp_List*) args->data, 0);

    if (self->type == state->Nil) {
        return lisp_String_from_ascii(state, "nil");
    } else {
        return lisp_Object_to_string(state, self);
    }
}
static lisp_Object* lisp_Nil_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_List* list = (lisp_List*) args->data;
    lisp_Object* self = lisp_List_get(state, list, 0);
    lisp_Object* other = lisp_List_get(state, list, 1);

    if (self->type == state->Nil && other->type == state->Nil) {
        return state->true;
    } else {
        return lisp_Object_equal(state, self, other) ? state->true : state->false;
    }
}

static void lisp_Nil_boot(lisp_State* state) {
    lisp_Object* Nil = state->Nil;
    lisp_List* values = (lisp_List*) Nil->values->data;
    lisp_Map* prototype = (lisp_Map*) lisp_List_get(state, values, LISP_IDX_TYPE_PROTOTYPE)->data;

    lisp_List_mut_set(values, LISP_IDX_TYPE_NAME, lisp_String_from_ascii(state, "Nil"));

    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "to-string"), lisp_Native_new(state, lisp_Nil_export_to_string));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "equal"), lisp_Native_new(state, lisp_Nil_export_equal));
}


#endif
