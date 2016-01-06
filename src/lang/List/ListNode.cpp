#ifndef __LISP_LANG_LIST_LIST_NODE_CPP__
#define __LISP_LANG_LIST_LIST_NODE_CPP__


namespace lisp {

    inline ListNode::ListNode(ListNode* n, Var<Value> v) {
        next = n;
        value = v;
    }

    inline ListNode::ListNode(ListNode& node) {
        ListNode* n = node.next;
        Var<Value> v = node.value;

        if (n != NULL) {
            next = new ListNode(*(n));
        } else {
            next = NULL;
        }

        if (!v.is_null()) {
            value = v;
        }
    }

    inline ListNode::~ListNode(void) {
        if (next != NULL) {
            delete next;
        }
    }
}


#endif
