#ifndef __LISP_LANG_VAR_H__
#define __LISP_LANG_VAR_H__


namespace lisp {
    template <typename Type>
    class Var {
        private:
            Type* _value;

        public:
            inline Var(void);
            inline Var(Type*);
            inline Var(Var<Type>&);
            inline ~Var(void);

            template <typename SubType>
            inline Var<SubType>& cast(void);

            inline bool is_null(void) const;
            inline Type* unwrap(void) const;

            inline Var<Type>& operator=(Var<Type>&);

            inline bool operator==(const Var<Type>&) const;
            inline bool operator!=(const Var<Type>&) const;
    };
}


#endif
