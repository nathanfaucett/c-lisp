#ifndef __LISP_GC_GC_DATA_H__
#define __LISP_GC_GC_DATA_H__


typedef struct lisp_GCData {
    uintsize bytes;
    void* data;
} lisp_GCData;

static lisp_GCData* lisp_GCData_new(uintsize bytes);
static void lisp_GCData_delete(lisp_GCData* gc_data);


#endif
