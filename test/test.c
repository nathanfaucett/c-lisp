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

static lisp_Value* list(lisp_State* state, lisp_Value* params, lisp_Scope* scope) {
    return params;
}

static lisp_Value* list_get(lisp_State* state, lisp_Value* params, lisp_Scope* scope) {
    lisp_Value* list = lisp_List_get(state, &params->list, 0);
    lisp_Value* index = lisp_List_get(state, &params->list, 1);
    return lisp_List_get(state, &list->list, lisp_Number_get_i32(&index->number));
}

static lisp_Value* equal(lisp_State* state, lisp_Value* params, lisp_Scope* scope) {
    return lisp_Value_boolean(state,
        lisp_Value_equal(
            lisp_List_get(state, &params->list, 0),
            lisp_List_get(state, &params->list, 1)
        )
    );
}

static lisp_Value* Number_mul(lisp_State* state, lisp_Value* params, lisp_Scope* scope) {
    lisp_Value* a = lisp_List_get(state, &params->list, 0);
    lisp_Value* b = lisp_List_get(state, &params->list, 1);

    if (a->type == b->type && a->type == LISP_TYPE_NUMBER) {
        if (a->number.is_f64 || b->number.is_f64) {
            return lisp_Value_number_from_f64(state,
                lisp_Number_get_f64(&a->number) * lisp_Number_get_f64(&b->number)
            );
        } else {
            return lisp_Value_number_from_i32(state,
                lisp_Number_get_i32(&a->number) * lisp_Number_get_i32(&b->number)
            );
        }
    } else {
        return lisp_Value_number_from_i32(state, 0);
    }
}

static lisp_Value* Number_sub(lisp_State* state, lisp_Value* params, lisp_Scope* scope) {
    lisp_Value* a = lisp_List_get(state, &params->list, 0);
    lisp_Value* b = lisp_List_get(state, &params->list, 1);

    if (a->type == b->type && a->type == LISP_TYPE_NUMBER) {
        if (a->number.is_f64 || b->number.is_f64) {
            return lisp_Value_number_from_f64(state,
                lisp_Number_get_f64(&a->number) - lisp_Number_get_f64(&b->number)
            );
        } else {
            return lisp_Value_number_from_i32(state,
                lisp_Number_get_i32(&a->number) - lisp_Number_get_i32(&b->number)
            );
        }
    } else {
        return lisp_Value_number_from_i32(state, 0);
    }
}


void test(void) {
    lisp_u8* file = read_file("test/test.lisp");

    if (file) {
        lisp_State* state = lisp_State_new();

        lisp_State_native(state, "list", list);
        lisp_State_native(state, "list-get", list_get);
        lisp_State_native(state, "=", equal);
        lisp_State_native(state, "*", Number_mul);
        lisp_State_native(state, "-", Number_sub);

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
}
