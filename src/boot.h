#ifndef __LISP_BOOT_H__
#define __LISP_BOOT_H__


static void lisp_boot(lisp_State* state);

static void lisp_boot_type (
    lisp_State* state,
    char* name,
    lisp_Object* type,
    lisp_Object* super,
    uintsize values,
    bool template,
    bool abstract,
    bool bytes,
    bool immutable
);

static lisp_Object* lisp_boot_object_alloc(lisp_State* state, lisp_Object* type);
static lisp_Object* lisp_boot_object_init(lisp_Object* object, lisp_GCHeader* gc_header, lisp_Object* type);
static lisp_Object* lisp_boot_object_size(lisp_State* state, lisp_Object* type, uintsize size);


#endif
