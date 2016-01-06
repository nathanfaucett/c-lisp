#ifndef __LISP_LANG_LIST_LIST_CPP__
#define __LISP_LANG_LIST_LIST_CPP__


namespace lisp {

    inline List::List(ListNode* root, ListNode* tail, u32 size) : Value() {
        _root = root;
        _tail = tail;
        _size = size;
    }

    inline ListNode* List::_get_node(u32 index) const {
        if (index == 0) {
            return _root;
        } else if (index == _size - 1) {
            return _tail;
        } else {
            u32 i = 0;
            ListNode* node = _root;

            while (node != NULL && i++ != index) {
                node = node->next;
            }

            return node;
        }
    }

    inline ListNode* List::_copy_with_new_tail(ListNode* node, ListNode* tail) const {
        if (node != NULL) {
            return new ListNode(_copy_with_new_tail(node->next, tail), node->value);
        } else {
            return tail;
        }
    }

    inline List::List(void) : Value() {
        _root = NULL;
        _tail = NULL;
        _size = 0;
    }

    inline List::~List(void) {
        if (_root != NULL) {
            delete _root;
        }
        if (_tail != NULL) {
            delete _tail;
        }
    }

    inline u32 List::size(void) const {
        return _size;
    }

    inline Var<Value> List::get(u32 index, Var<Value>& not_set) const {
        ListNode* node = _get_node(index);

        if (node != NULL) {
            return node->value;
        } else {
            return not_set;
        }
    }

    inline Var<Value> List::get(u32 index) const {
        ListNode* node = _get_node(index);

        if (node != NULL) {
            return node->value;
        }
    }

    inline i32 List::index_of(Var<Value>& value) const {
        ListNode* node = _root;
        u32 i = 0;

        while (node != NULL) {
            if (node->value == value) {
                return i;
            } else {
                node = node->next;
                i += 1;
            }
        }

        return -1;
    }

    inline Var<Value> List::unshift(Var<Value>& value) const {
        if (_root != NULL) {
            Var<Value> list(new List(new ListNode(_root, value), _tail, _size + 1));
            return list;
        } else {
            ListNode* root = new ListNode(NULL, value);
            Var<Value> list(new List(root, root, 1));
            return list;
        }
    }

    inline Var<Value> List::push(Var<Value>& value) const {
        if (_root != NULL) {
            ListNode* tail = new ListNode(NULL, value);
            ListNode* root = _copy_with_new_tail(_root, tail);
            Var<Value> list(new List(root, tail, _size + 1));
            return list;
        } else {
            ListNode* root = new ListNode(NULL, value);
            Var<Value> list(new List(root, root, 1));
            return list;
        }
    }
}


#endif
