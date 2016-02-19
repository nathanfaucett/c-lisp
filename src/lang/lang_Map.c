#ifndef __LISP_LANG_MAP_C__
#define __LISP_LANG_MAP_C__


static lisp_Object* lisp_Map_init(lisp_State* state, lisp_Object* map) {
    lisp_Object** values = (lisp_Object**) map->data;
    values[LISP_IDX_MAP_ENTIRES] = state->nil;
    return map;
}
static lisp_Object* lisp_Map_new_type(lisp_State* state, lisp_Object* type) {
    lisp_Object* object = lisp_boot_object_size(state, type, sizeof(void*));
    return lisp_Map_init(state, object);
}


#endif
