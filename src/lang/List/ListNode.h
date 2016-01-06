#ifndef __LISP_LANG_LIST_LIST_NODE_H__
#define __LISP_LANG_LIST_LIST_NODE_H__


namespace lisp {
    class ListNode {
        public:
            ListNode* next;
            Var<Value> value;

            inline ListNode(ListNode*, Var<Value>);
            inline ListNode(ListNode&);
            inline ~ListNode(void);
    };
}


#endif
