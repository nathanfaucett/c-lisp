#include <stdio.h>
#include "../lib.h"


int main() {
    lisp_State* state = lisp_State_new();

    lisp_Value* astring = lisp_Value_string_from_cstring(state, "Hello, ");
    lisp_Value* bstring = lisp_Value_string_from_cstring(state, "world!");

    lisp_Value* alist = lisp_Value_list(state);
    lisp_Value* blist = lisp_List_unshift(state, &alist->list, bstring);
    lisp_Value* clist = lisp_List_unshift(state, &blist->list, astring);

    lisp_Value* string = lisp_Value_to_string(state, clist);
    lisp_u8* cstr = lisp_String_to_cstring(&string->string);
    printf("%s\n", cstr);
    free(cstr);

    lisp_State_delete(state);
    return 0;
}
