#ifndef __LISP_LANG_NUMBER_C__
#define __LISP_LANG_NUMBER_C__


static lisp_Number* lisp_Number_from_i32(lisp_Number* number, lisp_i32 i32) {
    number->i32 = i32;
    number->is_f64 = LISP_FALSE;
    return number;
}

static lisp_Number* lisp_Number_from_f64(lisp_Number* number, lisp_f64 f64) {
    number->f64 = f64;
    number->is_f64 = LISP_TRUE;
    return number;
}

static lisp_i32 lisp_Number_get_i32(lisp_Number* number) {
    if (number->is_f64) {
        return (lisp_i32) number->f64;
    } else {
        return number->i32;
    }
}

static lisp_f64 lisp_Number_get_f64(lisp_Number* number) {
    if (number->is_f64) {
        return number->f64;
    } else {
        return (lisp_f64) number->i32;
    }
}

static lisp_Value* lisp_Number_to_string(lisp_State* state, lisp_Number* number) {
    lisp_Value* value;
    lisp_u8* cstring;

    if (number->is_f64) {
        cstring = lisp_dtoa(number->f64);
    } else {
        cstring = lisp_itoa(number->i32);
    }

    value = lisp_Value_string_from_cstring(state, cstring);
    free(cstring);

    return value;
}

static lisp_bool lisp_Number_equal(lisp_Number* a, lisp_Number* b) {
    if (a->is_f64) {
        return a->f64 == lisp_Number_get_f64(b);
    } else {
        if (b->is_f64) {
            return b->f64 == lisp_Number_get_f64(a);
        } else {
            return b->i32 == lisp_Number_get_i32(a);
        }
    }
}


#endif
