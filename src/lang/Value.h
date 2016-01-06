#ifndef __LISP_LANG_VALUE_H__
#define __LISP_LANG_VALUE_H__


namespace lisp {
    class Value {
        private:
            u32 _ref;

        public:
            inline Value(void);
            inline virtual ~Value(void);

            inline u32 ref(void);
            inline u32 deref(void);

            inline virtual Value& operator=(Value&);

            inline virtual bool operator==(const Value&) const;
            inline virtual bool operator!=(const Value&) const;

            inline virtual Var<Value> to_string(void);
    };
}


#endif
