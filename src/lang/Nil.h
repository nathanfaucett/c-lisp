#ifndef __LISP_LANG_NIL_H__
#define __LISP_LANG_NIL_H__


typedef struct lisp_Nil {
    struct lisp_Value* value;
} lisp_Nil;

static struct lisp_Value* lisp_Nil_to_string(lisp_State*);

static lisp_bool lisp_Nil_equal(lisp_Nil*, lisp_Nil*);


#endif
