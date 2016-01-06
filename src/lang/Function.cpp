#ifndef __LISP_LANG_FUNCTION_CPP__
#define __LISP_LANG_FUNCTION_CPP__


namespace lisp {

    inline Function::Function(Context* context, List* arguments, List* body) : Value(context) {
        _name = new String();
        _arguments = arguments;
        _body = body;
    }

    inline Function::Function(Context* context, List* arguments, List* body) : Value(context) {
        _name = name;
        _arguments = arguments;
        _body = body;
    }

    inline Function::~Function(void) {}

    inline Var<String> Function::to_string(void) const {
        return _body->to_string();
    }
}


#endif
