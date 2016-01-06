#ifndef __LISP_UTILS_ARRAY_H__
#define __LISP_UTILS_ARRAY_H__


namespace lisp {
    template <typename Type>
    class Array {
        private:
            Type* _array;
            u32 _size;

        public:
            inline Array(void);
			inline Array(const Array<Type>&);
			inline ~Array(void);

            inline Type operator[](i32) const;
		    inline Type& operator[](i32);

            inline u32 size(void);

            inline Array<Type>& push(const Type);
            inline Array<Type>& unshift(const Type);

            inline Type pop(void);
            inline Type shift(void);

            inline Array<Type>& empty(void);
            inline i32 index_of(const Type&) const;

            inline Array<Type>& splice(u32, u32);
            inline Array<Type>& splice(u32);

            inline Array<Type>& operator=(const Array<Type>&);
    };
}

#endif
