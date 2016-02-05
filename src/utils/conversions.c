#ifndef __LISP_UTILS_CONVERSIONS_C__
#define __LISP_UTILS_CONVERSIONS_C__


static lisp_i64 lisp_ascii_to_i64(lisp_char* ascii) {
    lisp_i64 result = 0;
    lisp_size i = 0;

    if (ascii[0] == '-') {
        result = -1;
        i = 1;
    }

    while (ascii[i] != '\0') {
        result = result * 10 + ascii[i] - '0';
        i += 1;
    }

    return result;
}
static lisp_size lisp_ascii_to_u64(lisp_char* ascii) {
    lisp_size result = 0;
    lisp_size i = 0;

    while (ascii[i] != '\0') {
        result = result * 10 + ascii[i] - '0';
        i += 1;
    }

    return result;
}

static lisp_f64 lisp_ascii_to_f64(lisp_char* ascii) {
    if (!ascii || !*ascii) {
        return 0;
    } else {
        lisp_f64 integer_part = 0;
        lisp_f64 fraction_part = 0;
        lisp_i64 divisor_for_fraction = 1;
        lisp_i64 sign = 1;
        lisp_bool in_fraction = LISP_FALSE;

        if (*ascii == '-') {
            ++ascii;
            sign = -1;
        } else if (*ascii == '+') {
            ++ascii;
        }

        while (*ascii != '\0') {
            if (*ascii >= '0' && *ascii <= '9') {
                if (in_fraction) {
                    fraction_part = fraction_part*10 + (*ascii - '0');
                    divisor_for_fraction *= 10;
                } else {
                    integer_part = integer_part*10 + (*ascii - '0');
                }
            } else if (*ascii == '.') {
                if (in_fraction) {
                    return sign * (integer_part + fraction_part/divisor_for_fraction);
                } else {
                    in_fraction = LISP_TRUE;
                }
            } else {
                return sign * (integer_part + fraction_part/divisor_for_fraction);
            }
            ++ascii;
        }

        return sign * (integer_part + fraction_part / divisor_for_fraction);
    }
}

static lisp_char* lisp_i64_to_ascii(lisp_i64 object) {
    static lisp_char buffer[LISP_INT_DIGITS + 2];
    lisp_char* ascii = buffer + LISP_INT_DIGITS + 1;

    if (object >= 0) {
        do {
            *--ascii = '0' + (object % 10);
            object /= 10;
        } while (object != 0);
    } else {
        do {
            *--ascii = '0' - (object % 10);
            object /= 10;
        } while (object != 0);

        *--ascii = '-';
    }

    return lisp_ascii_clone(ascii);
}
static lisp_char* lisp_size_to_ascii(lisp_size object) {
    static lisp_char buffer[LISP_INT_DIGITS + 2];
    lisp_char* ascii = buffer + LISP_INT_DIGITS + 1;

    do {
        *--ascii = '0' + (object % 10);
        object /= 10;
    } while (object != 0);

    return lisp_ascii_clone(ascii);
}

static lisp_char* lisp_f64_to_ascii(lisp_f64 object) {
    return lisp_i64_to_ascii((lisp_i64) object);
}

#endif
