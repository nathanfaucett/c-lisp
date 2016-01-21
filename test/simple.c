#include <stdio.h>
#include <stdlib.h>
#include "../lib.h"


int main(void) {
    lisp_State* state = lisp_State_new();

    lisp_Value* value = lisp_Value_new(state, state->type_string);
    lisp_String* string = (lisp_String*) value->value;

    lisp_String_from_ascii(state, string, "Hello, World!", 0);
    lisp_char* cstring = lisp_String_to_cstring(string);
    puts(cstring);
    free(cstring);

    lisp_State_delete(state);
    return 0;
}
