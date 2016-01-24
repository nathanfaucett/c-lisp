#ifndef __LISP_UTILS_CONVERSIONS_C__
#define __LISP_UTILS_CONVERSIONS_C__


static lisp_i64 lisp_cstring_to_i64(lisp_char* cstring) {
    lisp_i64 result = 0;
    lisp_u64 i = 0;

    if (*cstring == '-') {
        result = -1;
        i = 1;
    }

    while (cstring[i] != '\0') {
        result = result * 10 + cstring[i] - '0';
        i += 1;
    }

    return result;
}

static lisp_f64 lisp_cstring_to_f64(lisp_char* cstring) {
    if (!cstring || !*cstring) {
        return 0;
    } else {
        lisp_f64 integer_part = 0;
        lisp_f64 fraction_part = 0;
        lisp_i64 divisor_for_fraction = 1;
        lisp_i64 sign = 1;
        lisp_bool in_fraction = LISP_FALSE;

        if (*cstring == '-') {
            ++cstring;
            sign = -1;
        } else if (*cstring == '+') {
            ++cstring;
        }

        while (*cstring != '\0') {
            if (*cstring >= '0' && *cstring <= '9') {
                if (in_fraction) {
                    fraction_part = fraction_part*10 + (*cstring - '0');
                    divisor_for_fraction *= 10;
                } else {
                    integer_part = integer_part*10 + (*cstring - '0');
                }
            } else if (*cstring == '.') {
                if (in_fraction) {
                    return sign * (integer_part + fraction_part/divisor_for_fraction);
                } else {
                    in_fraction = LISP_TRUE;
                }
            } else {
                return sign * (integer_part + fraction_part/divisor_for_fraction);
            }
            ++cstring;
        }

        return sign * (integer_part + fraction_part / divisor_for_fraction);
    }
}

static lisp_char* lisp_i64_to_cstring(lisp_i64 value) {
    static lisp_char buffer[LISP_INT_DIGITS + 2];
    lisp_char* cstring = buffer + LISP_INT_DIGITS + 1;

    if (value >= 0) {
        do {
            *--cstring = '0' + (value % 10);
            value /= 10;
        } while (value != 0);
    } else {
        do {
            *--cstring = '0' - (value % 10);
            value /= 10;
        } while (value != 0);

        *--cstring = '-';
    }

    return lisp_cstring_clone(cstring);
}

static lisp_char* lisp_f64_to_cstring(lisp_f64 value) {
    return lisp_i64_to_cstring((lisp_i64) value);
}

#endif
