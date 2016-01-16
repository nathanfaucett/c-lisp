#ifndef __LISP_ARRAY_C__
#define __LISP_ARRAY_C__


static lisp_Array* lisp_Array_constructor(lisp_Array* array) {
    array->size = 0;
    array->slice = NULL;
    return array;
}

static void lisp_Array_destructor(lisp_Array* array) {\
    if (array->slice != NULL) {
        free(array->slice);
    }
}

static lisp_Array* lisp_Array_new(void) {
    return lisp_Array_constructor((lisp_Array*) malloc(sizeof(lisp_Array)));
}

static void lisp_Array_delete(lisp_Array* array) {
    lisp_Array_destructor(array);
    free(array);
}

static lisp_u32 lisp_Array_size(lisp_Array* array) {
    return array->size;
}

static lisp_i32 lisp_Array_index_of(lisp_Array* array, lisp_Value* value) {
    for (lisp_u32 i = 0, il = array->size; i < il; i++) {
        if (lisp_Value_equal(lisp_Array_get(array, i), value)) {
            return (lisp_i32) i;
        }
    }
    return -1;
}

static lisp_Value* lisp_Array_get(lisp_Array* array, lisp_u32 index) {
    if (index >= array->size) {
        return array->slice[array->size - 1];
    } else {
        return array->slice[index];
    }
}

static void lisp_Array_set(lisp_Array* array, lisp_u32 index, lisp_Value* value) {
    if (index < array->size) {
        array->slice[index] = value;
    }
}

static void lisp_Array_push(lisp_Array* array, lisp_Value* value) {
    lisp_u32 size = array->size;
    lisp_Value** slice = array->slice;
    lisp_Value** new_slice = (lisp_Value**) malloc((size + 1) * sizeof(lisp_Value*));

    if (slice != NULL) {
        lisp_values_copy(new_slice, slice, 0, size, 0);
        free(slice);
    }
    new_slice[size] = value;

    array->size = size + 1;
    array->slice = new_slice;
}

static void lisp_Array_remove(lisp_Array* array, lisp_u32 index) {
    lisp_u32 size = array->size;

    if (index < size) {
        lisp_Value** slice = array->slice;
        lisp_Value** new_slice = (lisp_Value**) malloc((size - 1) * sizeof(lisp_Value*));

        if (slice != NULL) {
            lisp_values_copy(new_slice, slice, 0, index, 0);
            lisp_values_copy(new_slice, slice, index + 1, size, index);
            free(slice);
        }

        array->size = size - 1;
        array->slice = new_slice;
    }
}


#endif
