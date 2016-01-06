#ifndef __LISP_LANG_FUNCTION_H__
#define __LISP_LANG_FUNCTION_H__


namespace lisp {
    class Function : public Value {
        private:
            String* _name;
            List* _arguments;
            List* _body;

        public:
            inline Function(Context*, List*, List*);
            inline Function(Context*, String*, List*, List*);
            inline virtual Var<String> to_string(void) const;
    };
}


#endif
