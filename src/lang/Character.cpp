#ifndef __LISP_LANG_CHARACTER_CPP__
#define __LISP_LANG_CHARACTER_CPP__


namespace lisp {

    inline u8* Character::_clone_bytes(void) const {
        u8* bytes = new u8[_size];

        for (u32 i = 0, il = _size; i < il; i++) {
            bytes[i] = _bytes[i];
        }

        return bytes;
    }

    inline Character::Character(void) : Value() {
        _size = 0;
        _bytes = new u8[_size];
        _bytes[0] = '\0';
    }

    inline Character::Character(u8 byte) : Value() {
        _size = 1;
        _bytes = new u8[_size];
        _bytes[0] = byte;
    }

    inline Character::Character(u8* bytes, u32 size) : Value() {
        _bytes = bytes;
        _size = size;
    }

    inline Character::Character(const Character& ch) : Value() {
        _size = ch.size();
        _bytes = ch._clone_bytes();
    }

    inline Character::Character(Var<Character> ref) : Value() {
        Character* ch = ref.unwrap();
        _size = ch->size();
        _bytes = ch->_clone_bytes();
    }

    inline Character::~Character(void) {
        delete[] _bytes;
    }

    inline u32 Character::size(void) const {
        return _size;
    }

    inline u8 Character::to_char(void) const {
        return _bytes[0];
    }

    inline u8* Character::get_bytes(void) const {
        return _bytes;
    }

    inline Character& Character::operator=(Character& ch) {
        delete[] _bytes;
        _size = ch.size();
        _bytes = ch._clone_bytes();
        return *this;
    }

    inline bool Character::operator==(const Character& ch) const {
        if (_size != ch._size) {
            return false;
        } else {
            for (u32 i = 0, il = _size; i < il; i++) {
                if (_bytes[i] != ch._bytes[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    inline bool Character::operator!=(const Character& ch) const {
        return !(*this == ch);
    }

    inline Var<Value> Character::to_string(void) {
        Var<Value> string(new String(_bytes));
        return string;
    }

    inline const u8* Character::to_cstring(void) const {
        return _clone_bytes();
    }
}


#endif
