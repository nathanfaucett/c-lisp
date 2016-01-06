#ifndef __LISP_LANG_NIL_H__
#define __LISP_LANG_NIL_H__


namespace lisp {
    class Nil : public Value {
        public:
            inline Nil(void);
            inline virtual Var<Value> to_string(void) const;
    };
}


#endif
