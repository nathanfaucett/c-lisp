#ifndef __LISP_ARRAY_H__
#define __LISP_ARRAY_H__


typedef struct lisp_Array {
    lisp_u32 size;
    struct lisp_Value** slice;
} lisp_Array;


static lisp_Array* lisp_Array_constructor(lisp_Array*);
static void lisp_Array_destructor(lisp_Array*);

static lisp_Array* lisp_Array_new(void);
static void lisp_Array_delete(lisp_Array*);

static lisp_u32 lisp_Array_size(lisp_Array*);
static lisp_i32 lisp_Array_index_of(lisp_Array*, struct lisp_Value*);

static struct lisp_Value* lisp_Array_get(lisp_Array*, lisp_u32);
static void lisp_Array_set(lisp_Array*, lisp_u32, struct lisp_Value*);

static void lisp_Array_push(lisp_Array*, struct lisp_Value*);
static void lisp_Array_remove(lisp_Array*, lisp_u32);


#endif
