#ifndef __LISP_LANG_SEQ_C__
#define __LISP_LANG_SEQ_C__


static void lisp_Seq_alloc(lisp_State* state, lisp_Value* value) {
    lisp_Seq* seq = (lisp_Seq*) value->data;
    seq->root = NULL;
    seq->tail = NULL;
    seq->size = 0;
}
static void lisp_Seq_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_Seq* seq = (lisp_Seq*) value->data;

    if (seq->root != NULL) {
        lisp_SeqNode_dealloc(seq->root);
    }
}
static void lisp_Seq_mark(lisp_Value* value) {
    lisp_Seq* seq = (lisp_Seq*) value->data;

    if (seq->root != NULL) {
        lisp_SeqNode_mark(seq->root);
    }
}

static lisp_SeqNode* lisp_Seq_find_node(lisp_Seq* seq, lisp_size index) {
    if (index == 0) {
        return seq->root;
    } else if (index == seq->size - 1) {
        return seq->tail;
    } else if (index < seq->size) {
        return lisp_SeqNode_find_node(seq->root, index);
    } else {
        return NULL;
    }
}

static lisp_size lisp_Seq_index_of(lisp_State* state, lisp_Seq* seq, lisp_Value* key) {
    lisp_SeqNode* node = seq->root;
    lisp_size index = 1;

    while (node != NULL) {
        if (lisp_Value_equal(state, node->value, key)) {
            return index;
        }
        index += 1;
        node = node->next;
    }

    return 0;
}

static lisp_Value* lisp_Seq_get(lisp_State* state, lisp_Seq* seq, lisp_size index) {
    lisp_SeqNode* node = lisp_Seq_find_node(seq, index);

    if (node != NULL) {
        return node->value;
    } else {
        return state->nil;
    }
}

static void lisp_Seq_set(lisp_Seq* seq, lisp_size index, lisp_Value* value) {
    lisp_SeqNode* node = lisp_Seq_find_node(seq, index);

    if (node != NULL) {
        node->value = value;
    }
}

static void lisp_Seq_push(lisp_Seq* seq, lisp_Value* value) {
    lisp_SeqNode* node = lisp_SeqNode_alloc(NULL, value);

    if (seq->root != NULL) {
        seq->tail->next = node;
        seq->tail = node;
    } else {
        seq->root = node;
        seq->tail = node;
    }

    seq->size += 1;
}

static void lisp_Seq_unshift(lisp_Seq* seq, lisp_Value* value) {
    lisp_SeqNode* node = lisp_SeqNode_alloc(seq->root, value);

    if (seq->root != NULL) {
        seq->root = node;
    } else {
        seq->root = node;
        seq->tail = node;
    }

    seq->size += 1;
}

static void lisp_Seq_pop(lisp_Seq* seq) {
    if (seq->size > 1) {
        lisp_SeqNode* tail = seq->tail;

        seq->tail = lisp_Seq_find_node(seq, seq->size - 2);
        lisp_SeqNode_dealloc(tail);

        seq->size -= 1;
    } else if (seq->size == 1) {
        lisp_SeqNode_dealloc(seq->tail);
        seq->root = NULL;
        seq->tail = NULL;
        seq->size = 0;
    }
}

static void lisp_Seq_shift(lisp_Seq* seq) {
    if (seq->size > 1) {
        lisp_SeqNode* root = seq->root;

        seq->root = root->next;
        lisp_SeqNode_dealloc(root);

        seq->size -= 1;
    } else if (seq->size == 1) {
        lisp_SeqNode_dealloc(seq->root);
        seq->root = NULL;
        seq->tail = NULL;
        seq->size = 0;
    }
}

static void lisp_Seq_remove(lisp_Seq* seq, lisp_size index) {
    if (index == 0) {
        lisp_Seq_shift(seq);
    } else if (index == seq->size - 1) {
        lisp_Seq_pop(seq);
    } else if (index < seq->size) {
        lisp_SeqNode* node = lisp_Seq_find_node(seq, index - 1);
        lisp_SeqNode* removed_node = node->next;

        node->next = removed_node->next;
        removed_node->next = NULL;

        lisp_SeqNode_dealloc(removed_node);

        seq->size -= 1;
    }
}

static lisp_bool lisp_Seq_equal(lisp_State* state, lisp_Seq* a, lisp_Seq* b) {
    if (a == b) {
        return LISP_TRUE;
    } else if (a->size != b->size) {
        return LISP_FALSE;
    } else {
        lisp_SeqNode* anode = a->root;
        lisp_SeqNode* bnode = b->root;

        while (anode != NULL) {
            if (lisp_Value_equal(state, anode->value, bnode->value)) {
                anode = anode->next;
                bnode = bnode->next;
            } else {
                return LISP_FALSE;
            }
        }

        return LISP_TRUE;
    }
}


#endif
