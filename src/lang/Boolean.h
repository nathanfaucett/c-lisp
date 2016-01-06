#ifndef __LISP_LANG_BOOLEAN_H__
#define __LISP_LANG_BOOLEAN_H__


namespace lisp {
    namespace lang {
        class Boolean : public Value {
            private:
                byte _value;

            public:
                inline Boolean(byte);
                inline Boolean(bool);

                inline byte get_value(void) const;

                inline virtual Var<Value> to_string(void);
        };
    }
}


#endif
