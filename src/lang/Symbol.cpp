#ifndef __LISP_LANG_SYMBOL_CPP__
#define __LISP_LANG_SYMBOL_CPP__


namespace lisp {

    inline Symbol::Symbol(const u8* cstring) : Value() {
        _value = new String(cstring);
    }
    inline Symbol::Symbol(const String& string) : Value() {
        _value = new String(string);
    }

    inline Var<Value> Symbol::to_string(void) {
        Var<Value> string(_value);
        return string;
    }
}


#endif
