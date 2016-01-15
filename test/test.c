#include <stdio.h>
#include "../lib.h"


int main() {
    lisp_State* state = lisp_State_new();

    lisp_Value* astring = lisp_Value_string_from_cstring(state, "Hello, ");
    lisp_Value* bstring = lisp_Value_string_from_cstring(state, "world!");

    lisp_Array* array = lisp_Array_new();
    lisp_Array_push(array, astring);
    lisp_Array_push(array, bstring);

    lisp_Value* vector = lisp_Value_vector_from_array(state, array);
    lisp_Value* value = lisp_Vector_get(state, &vector->vector, 0);

    lisp_Value* string = lisp_Value_to_string(state, value);
    lisp_u8* cstr = lisp_String_to_cstring(&string->string);
    printf("%s\n", cstr);
    free(cstr);

    lisp_Array_delete(array);
    lisp_State_delete(state);

    return 0;
}
