#ifndef __LISP_UTILS_H__
#define __LISP_UTILS_H__


namespace lisp {
    template <typename TypeA, typename TypeB, typename Return>
    inline Return array_copy(TypeA, TypeB, u32, u32, u32);

    inline u32 string_size(const u8*);
    inline const u8* string_copy(u8*, const u8*);
    inline const u8* string_clone(const u8*);
}

#endif
