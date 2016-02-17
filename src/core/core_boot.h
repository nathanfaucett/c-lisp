#ifndef __LISP_CORE_BOOT_H__
#define __LISP_CORE_BOOT_H__


static void lisp_boot(lisp_State* state);

static void lisp_boot_Type (
    lisp_State* state,
    struct lisp_Object* value,
    struct lisp_Object* super,
    uintsize size,
    uintsize values_size,
    bool abstract,
    bool bytes,
    void (*alloc)(lisp_State*, struct lisp_Object*),
    void (*mark)(struct lisp_Object*)
);


#endif
