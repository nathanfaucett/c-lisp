#ifndef __LISP_LANG_FUNCTION_C__
#define __LISP_LANG_FUNCTION_C__


static lisp_Object* lisp_Function_call(lisp_State* state, lisp_Object* fn, lisp_Object* args, lisp_Object* scope) {
    return args;
}

static lisp_bool lisp_Function_equal(lisp_State* state, lisp_Object* a, lisp_Object* b) {
    lisp_List* avalues = (lisp_List*) a->values->data;
    lisp_List* bvalues = (lisp_List*) b->values->data;

    return !(
        !lisp_Symbol_equal((lisp_Symbol*) lisp_List_get(state, avalues, 0)->data, (lisp_Symbol*) lisp_List_get(state, bvalues, 0)->data) || /* name */
        !lisp_List_equal(state, (lisp_List*) lisp_List_get(state, avalues, 1)->data, (lisp_List*) lisp_List_get(state, bvalues, 1)->data) || /* params */
        !lisp_List_equal(state, (lisp_List*) lisp_List_get(state, avalues, 2)->data, (lisp_List*) lisp_List_get(state, bvalues, 2)->data) || /* returns */
        !lisp_List_equal(state, (lisp_List*) lisp_List_get(state, avalues, 3)->data, (lisp_List*) lisp_List_get(state, bvalues, 3)->data) || /* bodies */
        !lisp_Map_equal(state, (lisp_Map*) lisp_List_get(state, avalues, 4)->data, (lisp_Map*) lisp_List_get(state, bvalues, 4)->data) /* templates */
    );
}

static lisp_Object* lisp_Function_export_call(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_List* list = (lisp_List*) args->data;
    lisp_Object* self = lisp_List_get(state, list, 0);
    lisp_Object* fn_args = lisp_List_get(state, list, 1);

    if (self->type == state->Function && fn_args->type == state->List) {
        return lisp_Function_call(state, self, fn_args, scope);
    } else {
        /* throw error */
        return state->nil;
    }
}
static lisp_Object* lisp_Function_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    return lisp_String_from_ascii(state, "(Function)");
}
static lisp_Object* lisp_Function_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope) {
    lisp_List* list = (lisp_List*) args->data;
    lisp_Object* self = lisp_List_get(state, list, 0);
    lisp_Object* other = lisp_List_get(state, list, 1);

    if (self->type == state->Function && other->type == state->Function) {
        return lisp_Function_equal(state, self, other) ? state->true : state->false;
    } else {
        return lisp_Object_equal(state, self, other) ? state->true : state->false;
    }
}

static void lisp_Function_boot(lisp_State* state) {
    lisp_Object* Function = state->Function;
    lisp_List* values = (lisp_List*) Function->values->data;

    lisp_List_mut_set(values, LISP_IDX_TYPE_NAME, lisp_String_from_ascii(state, "Function"));

    lisp_List* attributes = (lisp_List*) lisp_List_get(state, values, LISP_IDX_TYPE_ATTRIBUTES)->data;
    lisp_List_mut_set(attributes, 0, lisp_Symbol_from_ascii(state, "name"));
    lisp_List_mut_set(attributes, 1, lisp_Symbol_from_ascii(state, "params"));
    lisp_List_mut_set(attributes, 2, lisp_Symbol_from_ascii(state, "returns"));
    lisp_List_mut_set(attributes, 3, lisp_Symbol_from_ascii(state, "bodies"));
    lisp_List_mut_set(attributes, 4, lisp_Symbol_from_ascii(state, "templates"));

    lisp_List* types = (lisp_List*) lisp_List_get(state, values, LISP_IDX_TYPE_TYPES)->data;
    lisp_List_mut_set(types, 0, lisp_Annotation_new(state, state->Symbol));
    lisp_List_mut_set(types, 1, lisp_Annotation_new(state, state->List));
    lisp_List_mut_set(types, 2, lisp_Annotation_new(state, state->List));
    lisp_List_mut_set(types, 3, lisp_Annotation_new(state, state->List));
    lisp_List_mut_set(types, 4, lisp_Annotation_new(state, state->Map));

    lisp_Map* prototype = (lisp_Map*) lisp_List_get(state, values, LISP_IDX_TYPE_PROTOTYPE)->data;
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "call"), lisp_Native_new(state, lisp_Function_export_call));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "to-string"), lisp_Native_new(state, lisp_Function_export_to_string));
    lisp_Map_mut_set(state, prototype, lisp_Symbol_from_ascii(state, "equal"), lisp_Native_new(state, lisp_Function_export_equal));
}


#endif
