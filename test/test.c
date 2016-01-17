#include <stdio.h>
#include <stdlib.h>
#include "../lib.h"


char* read_file(char* filename) {
    char *buffer = NULL;
    int string_size,read_size;
    FILE *handler = fopen(filename, "r");

    if (handler) {
        fseek(handler,0,SEEK_END);
        string_size = ftell (handler);
        rewind(handler);

        buffer = (char*) malloc (sizeof(char) * (string_size + 1) );
        read_size = fread(buffer,sizeof(char),string_size,handler);
        buffer[string_size] = '\0';

        if (string_size != read_size) {
            free(buffer);
            buffer = NULL;
        }
    }

    return buffer;
}


int main() {
    lisp_u8* file = read_file("test/test.lisp");

    if (file) {
        lisp_State* state = lisp_State_new();
        lisp_Value* value = lisp_State_parse(state, file, state->global);
        free(file);

        if (value != NULL) {
            lisp_Value* string = lisp_Value_to_string(state, value);
            lisp_u8* cstring = lisp_String_to_cstring(&string->string);
            puts(cstring);
            free(cstring);
        }

        lisp_State_delete(state);
    } else {
        puts("error opening test file");
    }
    return 0;
}
