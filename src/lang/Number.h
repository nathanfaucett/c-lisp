#ifndef __LISP_LANG_NUMBER_H__
#define __LISP_LANG_NUMBER_H__


namespace lisp {
    class Number : public Value {
        private:
            bool _is_integer;
            bool _is_float;
            i32 _integer;
            f64 _float;

        public:
            inline Number(i32 value);
            inline Number(f64 value);

            inline i32 get_integer(void) const;
            inline f64 get_float(void) const;

            inline virtual Var<Value> to_string(void);
    };
}


#endif
