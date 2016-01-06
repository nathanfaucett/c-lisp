#ifndef __LISP_LANG_SYMBOL_H__
#define __LISP_LANG_SYMBOL_H__


namespace lisp {
    class Symbol : public Value {
        private:
            String* _value;

        public:
            inline Symbol(const u8* cstring);
            inline Symbol(const String& string);

            inline virtual Var<Value> to_string(void);
    };
}


#endif
