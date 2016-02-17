#ifndef __LISP_GC_GC_DATA_C__
#define __LISP_GC_GC_DATA_C__


static lisp_GCData* lisp_GCData_new(uintsize bytes) {
    lisp_GCData* gc_data = (lisp_GCData*) malloc(sizeof(lisp_GCData));
    gc_data->bytes = bytes;
    gc_data->data = malloc(bytes);
    return gc_data;
}
static void lisp_GCData_delete(lisp_GCData* gc_data) {
    free(gc_data->data);
    free(gc_data);
}


#endif
