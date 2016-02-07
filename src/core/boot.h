#ifndef __LISP_BOOT_H__
#define __LISP_BOOT_H__


static void lisp_boot(lisp_State* state);

static void lisp_boot_Type (
    lisp_State* state,
    struct lisp_Object* value,
    struct lisp_Object* super,
    lisp_size size,
    lisp_size values_size,
    lisp_bool abstract,
    lisp_bool bytes,
    void (*alloc)(lisp_State*, struct lisp_Object*),
    void (*mark)(struct lisp_Object*)
);


#endif
