#ifndef __LISP_GC_H__
#define __LISP_GC_H__


typedef struct lisp_GC {
    lisp_GCNode* root;
    lisp_usize size;
    lisp_usize bytes;
} lisp_GC;


static lisp_GC* lisp_GC_new(void);
static void lisp_GC_delete(lisp_GC* gc);

static lisp_GCNode* lisp_GC_alloc(lisp_GC* gc, lisp_usize bytes);
static void lisp_GC_dealloc(lisp_GC* gc, void* object);


#endif
