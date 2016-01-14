#ifndef __LISP_LANG_NUMBER_C__
#define __LISP_LANG_NUMBER_C__


static lisp_Number* lisp_Number_from_i32(lisp_Number* number, lisp_i32 i32) {
    number->i32 = i32;
    number->is_f64 = false;
    return number;
}

static lisp_Number* lisp_Number_from_f64(lisp_Number* number, lisp_f64 f64) {
    number->f64 = f64;
    number->is_f64 = true;
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
    return lisp_Value_string_from_cstring(state, "Number");
}


#endif
