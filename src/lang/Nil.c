#ifndef __LISP_LANG_NIL_C__
#define __LISP_LANG_NIL_C__


static lisp_Value* lisp_Nil_export_to_string(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return lisp_String_from_ascii(state, "nil");
}
static lisp_Value* lisp_Nil_export_equal(lisp_State* state, lisp_Value* args, lisp_Scope* scope) {
    return state->true;
}

static void lisp_Nil_boot(lisp_State* state) {
    /*
    lisp_Value* Nil = state->Nil;
    lisp_Map* prototype = (lisp_Map*) lisp_Array_get(state, (lisp_Array*) Nil->values->data, LISP_IDX_TYPE_PROTOTYPE)->data;
    */
}


#endif
