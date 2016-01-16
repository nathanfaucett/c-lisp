#include <stdio.h>
#include "../lib.hpp"


int main() {
    lisp_State* state = lisp_State_new();
    lisp_Reader* reader = lisp_Reader_new(state, "(+ 1 1 true false)");
    lisp_Value* list = lisp_Reader_next(reader, '\0');

    if (list != NULL) {
        lisp_Value* string = lisp_Value_to_string(state, list);
        lisp_u8* cstring = lisp_String_to_cstring(&string->string);
        puts(cstring);
        free(cstring);
    }

    lisp_Reader_delete(reader);
    lisp_State_delete(state);
    return 0;
}
