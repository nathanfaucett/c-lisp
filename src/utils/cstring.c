#ifndef __LISP_UTILS_CSTRING_C__
#define __LISP_UTILS_CSTRING_C__


static lisp_u64 lisp_cstring_size(lisp_char* cstring) {
    lisp_u64 size = 0;
    while (cstring[size] != '\0') {
        size += 1;
    }
    return size;
}

static lisp_char* lisp_cstring_copy(lisp_char* a, lisp_char* b) {
    for (lisp_u64 i = 0, il = lisp_cstring_size(b) + 1; i < il; i++) {
        a[i] = b[i];
    }
    return a;
}

static lisp_char* lisp_cstring_clone(lisp_char* cstring) {
    lisp_u64 size = lisp_cstring_size(cstring) + 1;
    lisp_char* other = (lisp_char*) malloc(size * sizeof(lisp_char));

    for (lisp_u64 i = 0, il = size; i < il; i++) {
        other[i] = cstring[i];
    }
    return other;
}

static lisp_bool lisp_cstring_equal(lisp_char* a, lisp_char* b) {
    for (lisp_u64 i = 0, il = lisp_cstring_size(a); i < il; i++) {
        if (a[i] != b[i]) {
            return LISP_FALSE;
        }
    }
    return LISP_TRUE;
}

#endif
