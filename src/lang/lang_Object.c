#ifndef __LISP_LANG_OBJECT_C__
#define __LISP_LANG_OBJECT_C__


static lisp_Object* lisp_Object_alloc(lisp_State* state, lisp_Object* type) {
    lisp_Object** type_values = (lisp_Object**) type->data;
    uintsize size = LISP_OBJECT_GET_DATA(type_values[LISP_IDX_TYPE_SIZE], uintsize);

    lisp_GCHeader* gc_header = lisp_State_alloc(state, sizeof(lisp_Object));
    lisp_Object* object = (lisp_Object*) gc_header->data;
    object->data = lisp_State_assoc(state, gc_header, size);
    object->type = type;

    return object;
}

bool lisp_Object_mark(lisp_Object* object) {
    if (lisp_GCHeader_mark(object->gc_header)) {
        lisp_Object** type_values = (lisp_Object**) object->type->data;

        if (LISP_OBJECT_GET_DATA(type_values[LISP_IDX_TYPE_BYTES], bool) == false) {
            lisp_Object** values = (lisp_Object**) object->data;

            uintsize i = 0,
                il = LISP_OBJECT_GET_DATA(type_values[LISP_IDX_TYPE_SIZE], uintsize);

            while (i < il) {
                lisp_Object_mark(values[i]);
                i += 1;
            }
        }

        return true;
    } else {
        return false;
    }
}
bool lisp_Object_equal(lisp_State* state, lisp_Object* a, lisp_Object* b) {
    if (a == b) {
        return true;
    } else if (a->type == b->type) {
        lisp_Object** type_values = (lisp_Object**) a->type->data;

        if (a->data == b->data) {
            return true;
        } else if (LISP_OBJECT_GET_DATA(type_values[LISP_IDX_TYPE_BYTES], bool) == false) {
            lisp_Object** avalues = (lisp_Object**) a->data;
            lisp_Object** bvalues = (lisp_Object**) b->data;

            uintsize i = 0,
                il = LISP_OBJECT_GET_DATA(type_values[LISP_IDX_TYPE_SIZE], uintsize);

            while (i < il) {
                if (!lisp_Object_equal(state, avalues[i], bvalues[i])) {
                    return false;
                }
                i += 1;
            }
            return true;
        } else {
            switch (LISP_OBJECT_GET_DATA(type_values[LISP_IDX_TYPE_SIZE], uintsize)) {
                case 1:
                    return LISP_OBJECT_GET_DATA(a, uint8) == LISP_OBJECT_GET_DATA(b, uint8);
                case 2:
                    return LISP_OBJECT_GET_DATA(a, uint16) == LISP_OBJECT_GET_DATA(b, uint16);
                case 4:
                    return LISP_OBJECT_GET_DATA(a, uint32) == LISP_OBJECT_GET_DATA(b, uint32);
                default:
                    return LISP_OBJECT_GET_DATA(a, uint64) == LISP_OBJECT_GET_DATA(b, uint64);
            }
        }
    } else {
        return false;
    }
}


#endif
