#ifndef __LISP_LANG_NUMBER_CPP__
#define __LISP_LANG_NUMBER_CPP__


namespace lisp {
    inline Number::Number(i32 value) : Value() {
        _integer = value;
        _is_integer = true;
        _is_float = false;
    }
    inline Number::Number(f64 value) : Value() {
        _float= value;
        _is_float = true;
        _is_integer = false;
    }

    inline i32 Number::get_integer(void) const {
        if (_is_integer) {
            return _integer;
        } else {
            return i32(_float);
        }
    }
    inline f64 Number::get_float(void) const {
        if (_is_integer) {
            return f64(_integer);
        } else {
            return _float;
        }
    }

    inline Var<Value> Number::to_string(void) {
        return Var<Value>(new String("Number"));
    }
}


#endif
