#ifndef __LISP_GC_GC_HEADER_H__
#define __LISP_GC_GC_HEADER_H__


typedef struct lisp_GCHeader {
    bool marked;
    uintsize bytes;
    void* data;
    struct lisp_GCHeaderNode* root;
} lisp_GCHeader;

static lisp_GCHeader* lisp_GCHeader_new(uintsize bytes);
static void lisp_GCHeader_delete(lisp_GCHeader* gc_header);

static void* lisp_GCHeader_assoc(struct lisp_GC* gc, lisp_GCHeader* gc_header, uintsize bytes);
static void lisp_GCHeader_dissoc(struct lisp_GC* gc, lisp_GCHeader* gc_header, void* data);

bool lisp_GCHeader_mark(lisp_GCHeader* gc_header);


#endif
