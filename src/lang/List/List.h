#ifndef __LISP_LANG_LIST_LIST_H__
#define __LISP_LANG_LIST_LIST_H__


namespace lisp {
    class List : public Value {
        private:
            ListNode* _root;
            ListNode* _tail;
            u32 _size;

            inline List(ListNode*, ListNode*, u32);
            inline ListNode* _get_node(u32) const;
            inline ListNode* _copy_with_new_tail(ListNode*, ListNode*) const;

        public:
            inline List(void);
            inline ~List(void);

            inline u32 size(void) const;

            inline Var<Value> get(u32, Var<Value>&) const;
            inline Var<Value> get(u32) const;

            inline i32 index_of(Var<Value>&) const;

            inline Var<Value> unshift(Var<Value>&) const;
            inline Var<Value> push(Var<Value>&) const;
    };
}


#endif
