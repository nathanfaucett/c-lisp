#ifndef __LISP_UTILS_CPP__
#define __LISP_UTILS_CPP__


namespace lisp {

    template <typename TypeA, typename TypeB, typename Return>
    inline Return array_copy(TypeA a, TypeB b, u32 start, u32 end, u32 dest) {
        for (u32 i = start, il = end, j = dest; i < il; i++, j++) {
            a[j] = b[i];
        }
        return a;
    }

    inline u32 string_size(const u8* string) {
        u32 size = 0;
        while (string[size] != '\0') {
            size += 1;
        }
        return size + 1;
    }

    inline const u8* string_copy(u8* a, const u8* b) {
        u32 size = string_size(b);
        return array_copy<u8*, const u8*, const u8*>(a, b, 0, size, 0);
    }

    inline const u8* string_clone(const u8* string) {
        u32 size = string_size(string);
        return array_copy<u8*, const u8*, const u8*>(new u8[size], string, 0, size, 0);
    }
}


#endif
