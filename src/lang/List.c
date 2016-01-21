#ifndef __LISP_LANG_LIST_C__
#define __LISP_LANG_LIST_C__


static lisp_ListNode* lisp_ListNode_constructor(lisp_ListNode* node, lisp_ListNode* next, lisp_Value* value) {
    node->ref_count = 1;
    node->next = next;
    node->value = value;
    return node;
}
static void lisp_ListNode_destructor(lisp_State* state, lisp_ListNode* node) {
    if (node->next != NULL) {
        lisp_ListNode_delete(state, node->next);
    }
    lisp_Value_deref(state, node->value);
}

static lisp_ListNode* lisp_ListNode_new(lisp_ListNode* next, lisp_Value* value) {
    return lisp_ListNode_constructor((lisp_ListNode*) malloc(sizeof(lisp_ListNode)), next, value);
}
static void lisp_ListNode_delete(lisp_State* state, lisp_ListNode* node) {
    lisp_ListNode_destructor(state, node);
    free(node);
}

static void lisp_ListNode_ref(lisp_ListNode* node) {
    node->ref_count += 1;
}
static void lisp_ListNode_deref(lisp_State* state, lisp_ListNode* node) {
    node->ref_count -= 1;

    if (node->ref_count == 0) {
        lisp_ListNode_delete(state, node);
    }
}


static void lisp_List_alloc(lisp_State* state, lisp_Value* value) {
    lisp_List* list = (lisp_List*) lisp_State_alloc(state, sizeof(lisp_List));
    value->value = list;
    list->root = NULL;
    list->tail = NULL;
    list->size = 0;
}
static void lisp_List_dealloc(lisp_State* state, lisp_Value* value) {
    lisp_List* list = (lisp_List*) value->value;

    if (list->root != NULL) {
        lisp_ListNode_deref(state, list->root);
    }
    lisp_State_dealloc(state, value->value);
}


#endif
