#include <stdio.h>
#include "../lib.h"


int main() {
    lisp_State state;
    lisp_State_new(&state);

    lisp_Value* astring = lisp_Value_cstring(&state, "Hello, ");
    lisp_Value_ref(astring);

    lisp_Value* bstring = lisp_Value_cstring(&state, "world!");
    lisp_Value_ref(bstring);

    lisp_Value* cstring = lisp_String_concat(&state, &astring->string, &bstring->string);
    lisp_Value_ref(cstring);

    lisp_u8* cstr = lisp_String_to_cstring(&cstring->string);
    printf("%s\n", cstr);
    free(cstr);

    lisp_State_delete(&state);
    return 0;
}
