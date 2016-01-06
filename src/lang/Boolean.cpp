#ifndef __LISP_LANG_BOOLEAN_CPP__
#define __LISP_LANG_BOOLEAN_CPP__


namespace lisp {
    namespace lang {

        inline Boolean::Boolean(byte value) : Value() {
            _value = value;
        }

        inline Boolean::Boolean(bool value) : Value() {
            _value = byte(value);
        }

        inline byte Boolean::get_value(void) const {
            return _value;
        }

        inline Var<Value> Boolean::to_string(void) const {
            if (_value != 0) {
                return Var<Value>(new String("true"));
            } else {
                return Var<Value>(new String("false"));
            }
        }
    }
}


#endif
