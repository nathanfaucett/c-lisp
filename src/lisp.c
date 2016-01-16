#ifndef __LISP_LISP_C__
#define __LISP_LISP_C__


CREATE_ARRAY_COPY(cstr, lisp_u8*, lisp_u8*, lisp_u8*);
CREATE_ARRAY_COPY(values, struct lisp_Value**, struct lisp_Value**, struct lisp_Value**);
CREATE_ARRAY_COPY(vector_nodes, struct lisp_VectorNode**, struct lisp_VectorNode**, struct lisp_VectorNode**);

static lisp_u32 lisp_cstring_size(lisp_u8* cstring) {
    lisp_u32 size = 0;
    while (cstring[size] != '\0') {
        size += 1;
    }
    return size;
}

static lisp_u8* lisp_cstring_copy(lisp_u8* a, lisp_u8* b) {
    lisp_u32 size = lisp_cstring_size(b) + 1;
    return lisp_cstr_copy(a, b, 0, size, 0);
}

static lisp_u8* lisp_cstring_clone(lisp_u8* cstring) {
    lisp_u32 size = lisp_cstring_size(cstring) + 1;
    return lisp_cstr_copy((lisp_u8*) malloc(size * sizeof(lisp_u8)), cstring, 0, size, 0);
}

static lisp_bool lisp_cstring_equal(lisp_u8* a, lisp_u8* b) {
    lisp_u32 asize = lisp_cstring_size(a);
    lisp_u32 bsize = lisp_cstring_size(b);

    if (asize != bsize) {
        return LISP_FALSE;
    } else {
        for (lisp_u32 i = 0, il = asize; i < il; i++) {
            if (a[i] != b[i]) {
                return LISP_FALSE;
            }
        }
        return LISP_TRUE;
    }
}

static void lisp_cstring_reverse(lisp_u8* cstring) {
    lisp_u8 ch;

    for (lisp_u32 i = 0, j = lisp_cstring_size(cstring) - 1; i < j; i++, j--) {
        ch = cstring[i];
        cstring[i] = cstring[j];
        cstring[j] = ch;
    }
}


#endif
