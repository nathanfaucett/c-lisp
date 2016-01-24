#ifndef __LISP_UTILS_CHAR_C__
#define __LISP_UTILS_CHAR_C__


static lisp_bool lisp_is_whitespace(lisp_u32 ch) {
    return (
        (ch >= 0x0009 && ch <= 0x000D) ||
        ch == 0x0020 ||
        ch == 0x0085 ||
        ch == 0x00A0 ||
        ch == 0x2028 ||
        ch == 0x2029
    );
}
static lisp_bool lisp_is_numeric(lisp_u32 ch) {
    return ch >= 0x30 && ch <= 0x39;
}
static lisp_u32 lisp_escape(lisp_u32 ch) {
    switch ((lisp_char) ch) {
        case 't':
            return '\t';
        case 'r':
            return '\r';
        case 'n':
            return '\n';
        case 'b':
            return '\b';
        case 'f':
            return '\f';
        default:
            return ch;
    }
}


#endif
