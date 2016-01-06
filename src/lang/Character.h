#ifndef __LISP_LANG_CHARACTER_H__
#define __LISP_LANG_CHARACTER_H__


namespace lisp {
    class Character : public Value {
        private:
            u8* _bytes;
            u32 _size;

            inline u8* _clone_bytes(void) const;

        public:
            inline Character();
            inline Character(u8);
            inline Character(u8*, u32);
            inline Character(const Character&);
            inline Character(Var<Character>);
            inline ~Character(void);

            inline u32 size(void) const;
            inline u8 to_char(void) const;
            inline u8* get_bytes(void) const;

            inline Character& operator=(Character&);

            inline bool operator==(const Character&) const;
            inline bool operator!=(const Character&) const;

            inline virtual Var<Value> to_string(void);
            inline virtual const u8* to_cstring(void) const;
    };
}


#endif
