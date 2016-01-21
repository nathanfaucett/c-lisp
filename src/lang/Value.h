#ifndef __LISP_LANG_VALUE_H__
#define __LISP_LANG_VALUE_H__


typedef struct lisp_Value {
    lisp_u64 ref_count;
    lisp_Type* type;
    void* value;
    struct lisp_Value* values;
} lisp_Value;

static struct lisp_Value* lisp_Value_new(lisp_State* state, lisp_Type* type);
static void lisp_Value_delete(lisp_State* state, lisp_Value* value);

void lisp_Value_ref(lisp_Value* value);
void lisp_Value_deref(lisp_State* state, lisp_Value* value);


#endif
