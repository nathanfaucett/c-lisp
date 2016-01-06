#ifndef __LISP_LANG_VAR_CPP__
#define __LISP_LANG_VAR_CPP__


namespace lisp {

    template <typename Type>
    inline Var<Type>::Var(void) {
        _value = NULL;
    }

    template <typename Type>
    inline Var<Type>::Var(Type* value) {
        if (value != NULL) {
            value->ref();
        }
        _value = value;
    }

    template <typename Type>
    inline Var<Type>::Var(Var<Type>& var) {
        _value = var._value;
        _value->ref();
    }

    template <typename Type>
    inline Var<Type>::~Var(void) {
        _value->deref();
    }

    template <typename Type>
    template <typename SubType>
    inline Var<SubType>& Var<Type>::cast(void) {
        SubType* value = static_cast<SubType*>(_value);
        Var<SubType> var(value);
        return var;
    }

    template <typename Type>
    inline bool Var<Type>::is_null(void) const {
        return _value == NULL;
    }

    template <typename Type>
    inline Type* Var<Type>::unwrap(void) const {
        return _value;
    }

    template <typename Type>
    inline Var<Type>& Var<Type>::operator=(Var<Type>& other) {
        _value = other._value;
        return *this;
    }

    template <typename Type>
    inline bool Var<Type>::operator==(const Var<Type>& other) const {
        return _value == other._value;
    }

    template <typename Type>
    inline bool Var<Type>::operator!=(const Var<Type>& other) const {
        return _value != other._value;
    }
}


#endif
