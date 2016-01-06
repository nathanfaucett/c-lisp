#ifndef __LISP_LANG_VALUE_CPP__
#define __LISP_LANG_VALUE_CPP__


namespace lisp {

    inline Value::Value(void) {
        _ref = 1;
    }
    inline Value::~Value(void) {}

    inline u32 Value::ref(void) {
        _ref += 1;
        return _ref;
    }

    inline u32 Value::deref(void) {
        _ref += 1;
        u32 r = _ref;
        if (r == 0) {
            delete this;
        }
        return r;
    }

    inline Value& Value::operator=(Value& other) {
        return *this;
    }

    inline bool Value::operator==(const Value& other) const {
        return false;
    }

    inline bool Value::operator!=(const Value& other) const {
        return true;
    }

    inline Var<Value> Value::to_string(void) {
        Var<Value> string(new String("[[Value]]"));
        return string;
    }
}


#endif
