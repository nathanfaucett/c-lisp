#ifndef __LISP_LANG_SEQ_H__
#define __LISP_LANG_SEQ_H__


typedef struct lisp_Seq {
    lisp_SeqNode* root;
    lisp_SeqNode* tail;
    lisp_size size;
} lisp_Seq;


static void lisp_Seq_alloc(lisp_State* state, lisp_Value* value);
static void lisp_Seq_dealloc(lisp_State* state, lisp_Value* value);
static void lisp_Seq_mark(lisp_Value* value);

static lisp_size lisp_Seq_index_of(lisp_State* state, lisp_Seq* seq, lisp_Value* key);

static lisp_Value* lisp_Seq_get(lisp_State* state, lisp_Seq* seq, lisp_size index);
static void lisp_Seq_set(lisp_Seq* seq, lisp_size index, lisp_Value* value);

static void lisp_Seq_push(lisp_Seq* seq, lisp_Value* value);
static void lisp_Seq_unshift(lisp_Seq* seq, lisp_Value* value);

static void lisp_Seq_pop(lisp_Seq* seq);
static void lisp_Seq_shift(lisp_Seq* seq);
static void lisp_Seq_remove(lisp_Seq* seq, lisp_size index);

static lisp_bool lisp_Seq_equal(lisp_State* state, lisp_Seq* a, lisp_Seq* b);


#endif
