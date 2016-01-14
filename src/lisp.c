#ifndef __LISP_LISP_C__
#define __LISP_LISP_C__


CREATE_ARRAY_COPY(cstring, lisp_u8*, lisp_u8*, lisp_u8*);

inline lisp_u32 cstring_size(lisp_u8* string) {
    lisp_u32 size = 0;
    while (string[size] != '\0') {
        size += 1;
    }
    return size;
}

inline lisp_u8* cstring_copy(lisp_u8* a, lisp_u8* b) {
    lisp_u32 size = cstring_size(b) + 1;
    return cstring_array_copy(a, b, 0, size, 0);
}

inline lisp_u8* cstring_clone(lisp_u8* string) {
    lisp_u32 size = cstring_size(string) + 1;
    return cstring_array_copy((lisp_u8*) malloc(size * sizeof(lisp_u8)), string, 0, size, 0);
}


#endif
