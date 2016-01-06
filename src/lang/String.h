#ifndef __LISP_LANG_STRING_H__
#define __LISP_LANG_STRING_H__


namespace lisp {
    class String : public Value {
        private:
            Character** _chars;
            u32 _size;

            inline String(const String&, const String&);
            inline Character** _clone_chars(void) const;

        public:
            inline String(void);
            inline String(const u8*);
            inline String(const String&);
            inline ~String(void);

            inline u32 size(void) const;

            inline Var<Character> char_at(u32) const;
            inline Var<String> concat(const String&) const;
            inline Var<String> concat(Var<String>) const;

            inline virtual bool operator==(const String&) const;
            inline virtual bool operator!=(const String&) const;

            inline virtual Var<Value> to_string(void);
            inline virtual const u8* to_cstring(void) const;
    };
}


#endif
