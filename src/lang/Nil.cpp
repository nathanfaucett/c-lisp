#ifndef __LISP_LANG_NIL_CPP__
#define __LISP_LANG_NIL_CPP__


namespace lisp {

    inline Nil::Nil(void) : Value() {}

    inline Var<Value> Nil::to_string(void) const {
        Var<Value> string(new String("nil"));
        return string;
    }
}


#endif
