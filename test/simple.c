#include <stdio.h>
#include <stdlib.h>
#include "../lib.h"


int main(void) {
    lisp_State* state = lisp_State_new();
    puts("=============================");
    printf("Object Count: %i\nTotal Bytes: %i\n", (int) state->gc->size, (int) state->gc->bytes);
    puts("=============================");
    lisp_State_delete(state);
    return 0;
}
