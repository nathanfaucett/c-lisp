#ifndef __LISP_LANG_BOOLEAN_H__
#define __LISP_LANG_BOOLEAN_H__


typedef struct lisp_Boolean {
    struct lisp_Value* value;
    lisp_bool boolean_value;
} lisp_Boolean;

static lisp_Boolean* lisp_Boolean_constructor(lisp_Boolean*, lisp_bool);

static struct lisp_Value* lisp_Boolean_to_string(lisp_State*, lisp_Boolean*);

static lisp_bool lisp_Boolean_equal(lisp_Boolean*, lisp_Boolean*);


#endif
