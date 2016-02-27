#include <stdio.h>
#include <stdlib.h>
#include "../lib.h"


int main(void) {
    char* code = "(10 symbol :keyword {:key \"Hello, World!\"} [0, 1] 'a')";

    lisp_State* state = lisp_State_new();
    lisp_Object* reader = lisp_Reader_new(state);
    lisp_Object* input = lisp_Reader_ascii_next(state, reader, code, '\0');

    printf("%i\n", (int) lisp_List_size(input));

    puts("=============================");
    printf("Object Count: %i\nTotal Bytes: %i\n", (int) state->gc->size, (int) state->gc->bytes);
    puts("=============================");
    lisp_State_delete(state);
    return 0;
}
