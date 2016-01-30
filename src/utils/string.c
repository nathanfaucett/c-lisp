#ifndef __LISP_UTILS_CSTRING_C__
#define __LISP_UTILS_CSTRING_C__


static lisp_size lisp_ascii_size(lisp_char* ascii) {
    lisp_size size = 0;
    while (ascii[size] != '\0') {
        size += 1;
    }
    return size;
}
static lisp_char* lisp_ascii_copy(lisp_char* a, lisp_char* b) {
    for (lisp_size i = 0, il = lisp_ascii_size(b) + 1; i < il; i++) {
        a[i] = b[i];
    }
    return a;
}
static lisp_char* lisp_ascii_clone(lisp_char* ascii) {
    lisp_size size = lisp_ascii_size(ascii) + 1;
    lisp_char* other = (lisp_char*) malloc(size * sizeof(lisp_char));

    for (lisp_size i = 0, il = size; i < il; i++) {
        other[i] = ascii[i];
    }
    return other;
}
static lisp_size lisp_ascii_index_of(lisp_char* ascii, lisp_char ch) {
    lisp_size index = 0;
    lisp_char c = ascii[index];

    while (c != '\0') {
        if (c == ch) {
            return index + 1;
        }
        index = index + 1;
        c = ascii[index];
    }

    return 0;
}
static lisp_bool lisp_ascii_equal(lisp_char* a, lisp_char* b) {
    lisp_size index = 0;
    lisp_char ch = a[index];

    while (ch != '\0') {
        if (ch != b[index]) {
            return LISP_FALSE;
        }
        index += 1;
        ch = a[index];
    }

    return LISP_TRUE;
}

static lisp_size lisp_utf8_size(lisp_u32* utf8) {
    lisp_size size = 0;
    while (utf8[size] != '\0') {
        size += 1;
    }
    return size;
}
static lisp_u32* lisp_utf8_copy(lisp_u32* a, lisp_u32* b) {
    for (lisp_size i = 0, il = lisp_utf8_size(b) + 1; i < il; i++) {
        a[i] = b[i];
    }
    return a;
}
static lisp_u32* lisp_utf8_clone(lisp_u32* utf8) {
    lisp_size size = lisp_utf8_size(utf8) + 1;
    lisp_u32* other = (lisp_u32*) malloc(size * sizeof(lisp_u32));

    for (lisp_size i = 0, il = size; i < il; i++) {
        other[i] = utf8[i];
    }
    return other;
}
static lisp_size lisp_utf8_index_of(lisp_u32* utf8, lisp_u32 ch) {
    lisp_size index = 0;
    lisp_u32 c = utf8[index];

    while (c != '\0') {
        if (c == ch) {
            return index + 1;
        }
        index = index + 1;
        c = utf8[index];
    }

    return 0;
}
static lisp_bool lisp_utf8_equal(lisp_u32* a, lisp_u32* b) {
    lisp_size index = 0;
    lisp_u32 ch = a[index];

    while (ch != '\0') {
        if (ch != b[index]) {
            return LISP_FALSE;
        }
        index += 1;
        ch = a[index];
    }

    return LISP_TRUE;
}

static lisp_bool lisp_ascii_utf8_equal(lisp_u32* a, lisp_char* b) {
    lisp_size index = 0;
    lisp_u32 ch = a[index];

    while (ch != '\0') {
        if (ch != (lisp_u32) b[index]) {
            return LISP_FALSE;
        }
        index += 1;
        ch = a[index];
    }

    return LISP_TRUE;
}

#endif
