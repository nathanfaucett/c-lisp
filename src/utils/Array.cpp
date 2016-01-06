#ifndef __LISP_UTILS_ARRAY_CPP__
#define __LISP_UTILS_ARRAY_CPP__


namespace lisp {
    template <typename Type>
    inline Array<Type>::Array(void) {
		_size = 0;
		_array = new Type[0];
	}

    template <typename Type>
    inline Array<Type>::Array(const Array<Type>& other) {
		_size = other._size;
        _array = array_copy<Type*, Type*, Type*>(new Type[_size], other._array, 0, _size, 0);
	}

    template <typename Type>
    inline Array<Type>::~Array(void) {
		delete[] _array;
	}

    template <typename Type>
    inline Type Array<Type>::operator[](i32 index) const {
	    return _array[(index >= i32(_size) ? (_size - 1) : index < 0 ? 0 : index)];
    }

    template <typename Type>
    inline Type& Array<Type>::operator[](i32 index) {
	    return _array[(index >= i32(_size) ? (_size - 1) : index < 0 ? 0 : index)];
    }

    template <typename Type>
    inline u32 Array<Type>::size(void) {
        return _size;
    }

    template <typename Type>
    inline Array<Type>& Array<Type>::push(const Type value) {
        u32 size = _size + 1;
        Type* array = array_copy<Type*, Type*, Type*>(new Type[size], _array, 0, _size, 0);
        array[_size] = value;
        _size = size;
        delete[] _array;
        _array = array;
        return *this;
    }

    template <typename Type>
    inline Array<Type>& Array<Type>::unshift(const Type value) {
        u32 size = _size + 1;
        Type* array = array_copy<Type*, Type*, Type*>(new Type[size], _array, 0, _size, 1);
        array[0] = value;
        _size = size;
        delete[] _array;
        _array = array;
        return *this;
    }

    template <typename Type>
    inline Type Array<Type>::pop(void) {
        u32 size = _size - 1;
        Type value = _array[size];
        Type* array = array_copy<Type*, Type*, Type*>(new Type[size], _array, 0, size, 0);
        _size = size;
        delete[] _array;
        _array = array;
        return value;
    }

    template <typename Type>
    inline Type Array<Type>::shift(void) {
        u32 size = _size - 1;
        Type value = _array[0];
        Type* array = array_copy<Type*, Type*, Type*>(new Type[size], _array, 1, _size, 0);
        _size = size;
        delete[] _array;
        _array = array;
        return value;
    }

    template <typename Type>
    inline Array<Type>& Array<Type>::empty(void) {
		_size = 0;
        delete[] _array;
		_array = new Type[0];
        return *this;
    }

    template <typename Type>
    inline i32 Array<Type>::index_of(const Type& value) const {
        for (u32 i = 0, il = _size; i < il; i++) {
            if (_array[i] == value) {
                return i;
            }
        }
        return -1;
    }

    template <typename Type>
    inline Array<Type>& Array<Type>::splice(u32 index, u32 count) {
        u32 start = index,
            end = index + count,
            size = _size - count;

        if (size == 0) {
            return empty();
        } else {
            if (end > _size) {
                end = _size;
            }

            if (start >= end) {
                return *this;
            } else {
                Type* array = new Type[size];

                array_copy<Type*, Type*, Type*>(array, _array, 0, start, 0);
                array_copy<Type*, Type*, Type*>(array, _array, end, _size, start);

                _size = size;
                delete[] _array;
                _array = array;

                return *this;
            }
        }
    }

    template <typename Type>
    inline Array<Type>& Array<Type>::splice(u32 index) {
        return splice(index, 1);
    }

    template <typename Type>
    inline Array<Type>& Array<Type>::operator=(const Array<Type>& other) {
		_size = other._size;
        delete[] _array;
        _array = array_copy<Type*, Type*, Type*>(new Type[_size], other._array, 0, _size, 0);
        return *this;
    }
}

#endif
