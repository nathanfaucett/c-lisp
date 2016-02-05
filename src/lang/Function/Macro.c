#ifndef __LISP_LANG_MACRO_C__
#define __LISP_LANG_MACRO_C__


static lisp_Object* lisp_Macro_call(lisp_State* state, lisp_Object* macro, lisp_Object* args, lisp_Object* scope) {
    return NULL;
}

static void lisp_Macro_boot(lisp_State* state) {
    /*
    lisp_Object* Macro = state->Macro;
    lisp_Map* prototype = (lisp_Map*) lisp_List_get(state, (lisp_List*) Macro->values->data, LISP_IDX_TYPE_PROTOTYPE)->data;
    */
}


#endif
