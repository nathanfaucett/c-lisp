#ifndef __LISP_NUMBERS_C__
#define __LISP_NUMBERS_C__


static lisp_i32 lisp_atoi(lisp_u8* cstring) {
    lisp_i32 result = 0;
    lisp_u32 i = 0;

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

static lisp_f64 lisp_atod(lisp_u8* cstring) {
    if (!cstring || !*cstring) {
        return 0;
    } else {
        lisp_f64 integer_part = 0;
        lisp_f64 fraction_part = 0;
        lisp_i32 divisor_for_fraction = 1;
        lisp_i32 sign = 1;
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

#define LISP_INT_DIGITS 19

static lisp_u8* lisp_itoa(lisp_i32 value) {
    static lisp_u8 buffer[LISP_INT_DIGITS + 2];
    lisp_u8* cstring = buffer + LISP_INT_DIGITS + 1;

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

static lisp_u8* lisp_dtoa(lisp_f64 value) {
    return NULL;
}

#endif
