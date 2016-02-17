#ifndef __LISP_GC_GC_H__
#define __LISP_GC_GC_H__


typedef struct lisp_GC {
    lisp_GCNode* root;
    uintsize size;
    uintsize bytes;
} lisp_GC;


static lisp_GC* lisp_GC_new(void);
static void lisp_GC_delete(lisp_GC* gc);

static lisp_GCHeader* lisp_GC_alloc(lisp_GC* gc, uintsize bytes);
static void lisp_GC_dealloc(lisp_GC* gc, lisp_GCHeader* gc_header);


#endif
