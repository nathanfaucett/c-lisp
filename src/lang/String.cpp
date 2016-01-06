#ifndef __LISP_LANG_STRING_CPP__
#define __LISP_LANG_STRING_CPP__


namespace lisp {
    // private
    inline String::String(const String& a, const String& b) : Value() {
        _size = a._size + b._size;
        _chars = new Character*[_size];

        for (u32 i = 0, il = a._size; i < il; i++) {
            _chars[i] = a._chars[i];
        }
        for (u32 i = a._size, il = _size, j = 0; i < il; i++, j++) {
            _chars[i] = a._chars[j];
        }
    }

    inline Character** String::_clone_chars(void) const {
        Character** chars = new Character*[_size];

        for (u32 i = 0, il = _size; i < il; i++) {
            chars[i] = _chars[i];
        }

        return chars;
    }

    inline String::String(void) : Value() {
        _size = 0;
        _chars = new Character*[0];
    }

    inline String::String(const u8* cstring) : Value() {
        u8 ch = cstring[0];
        u32 index = 0;

        while (ch != '\0') {
            index += 1;
            ch = cstring[index];
        }

        _size = index;
        _chars = new Character*[_size];

        index = 0;
        ch = cstring[index];

        while (ch != '\0') {
            _chars[index] = new Character(ch);
            index += 1;
            ch = cstring[index];
        }
    }

    inline String::String(const String& string) : Value() {
        _size = string.size();
        _chars = string._clone_chars();
    }

    inline String::~String(void) {
        delete[] _chars;
    }

    inline u32 String::size(void) const {
        return _size;
    }

    inline Var<Character> String::char_at(u32 index) const {
        if (index >= _size) {
            Var<Character> ch(new Character('\0'));
            return ch;
        } else {
            Var<Character> ch(_chars[index]);
            return ch;
        }
    }

    inline Var<String> String::concat(const String& other) const {
        Var<String> string(new String(*this, other));
        return string;
    }

    inline Var<String> String::concat(Var<String> other) const {
        Var<String> string(new String(*this, *(other.unwrap())));
        return string;
    }

    inline bool String::operator==(const String& other) const {
        if (_size != other._size) {
            return false;
        } else {
            for (u32 i = 0, il = _size; i < il; i++) {
                if (_chars[i] != other._chars[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    inline bool String::operator!=(const String& other) const {
        return !(*this == other);
    }

    inline Var<Value> String::to_string(void) {
        Var<Value> string(this);
        return string;
    }

    inline const u8* String::to_cstring(void) const {
        u8* cstr = new u8[_size + 1];

        for (u32 i = 0, il = _size; i < il; i++) {
            cstr[i] = _chars[i]->to_char();
        }
        cstr[_size] = '\0';

        return cstr;
    }
};


#endif
