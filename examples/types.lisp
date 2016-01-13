(defstruct ListNode <Type ^Any>
    [next ^ListNode<Type> value ^Type])

(defn list_node-create <Type ^Any>
    [next ^ListNode<Type> value ^Type] ^ListNode<Type>
    (ListNode<Type> next value))

(defstruct List <Type ^Any>
    [root ^ListNode<Type> tail ^ListNode<Type>  size ^Int32] ^Indexed)

(defn list-create <Type ^Any>
    [] ^List<Type>
    (List nil nil 0))

(def EMPTY_LIST ^List<Any ^Any> (list-create <Any>))


(defstruct Int [value ^c_int32] ^Number
    (add [self ^This other ^Int] ^Int
        (Int (c_call "lisp_int32_add" (.value self) (.value other))))
    (sub [self ^This other ^Int] ^Int
        (Int (c_call "lisp_int32_add" (.value self) (.value other)))))
