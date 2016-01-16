#include <stdio.h>
#include "../lib.h"


int main() {
    lisp_State* state = lisp_State_new();
    lisp_Reader* reader = lisp_Reader_new(state, "0");
    lisp_Value* zero = lisp_Reader_next(reader);

    if (zero != NULL) {
        lisp_Value* string = lisp_Value_to_string(state, zero);
        lisp_u8* cstring = lisp_String_to_cstring(&string->string);
        puts(cstring);
        free(cstring);
    }

    lisp_Reader_delete(reader);
    lisp_State_delete(state);
    return 0;
}
