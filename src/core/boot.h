#ifndef __LISP_BOOT_H__
#define __LISP_BOOT_H__


static void lisp_boot(lisp_State* state);

static void lisp_boot_MainType(lisp_State* state, struct lisp_Object* type);
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

static struct lisp_Object* lisp_boot_alloc_object(lisp_State* state, struct lisp_Object* type);
static struct lisp_Object* lisp_boot_init_object(struct lisp_Object* object, lisp_GCNode* gc_node, struct lisp_Object* type);
static struct lisp_Object* lisp_boot_new_size(lisp_State* state, struct lisp_Object* type, lisp_size size);
static struct lisp_Object* lisp_boot_new_list(lisp_State* state);
static struct lisp_Object* lisp_boot_new_list_node(lisp_State* state);
static struct lisp_Object* lisp_boot_new_map(lisp_State* state);
static struct lisp_Object* lisp_boot_new_bool(lisp_State* state, lisp_bool value);
static struct lisp_Object* lisp_boot_assoc_size(lisp_State* state, lisp_GCNode* gc_node, struct lisp_Object* type, lisp_size size);


#endif
