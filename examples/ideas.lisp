(defn ! [value] ^Boolean
    (__NATIVE_NOT_FUNCTION__ value))

(defn !! [value] ^Boolean
    (__NATIVE_BOOL_CAST__ value))

(defn = [a b] ^Boolean
    (__NATIVE_EQUAL__ a b))

(defn != [a b] ^Boolean
    (__NATIVE_NOT_EQUAL__ a b))

(defn factorial [x ^Int] ^Int
    (if (= x 0) 1
        (* x (factorial (- x 1)))))

(defn simple-reduce
    [array ^Indexed func ^Function]
        ((fn next [value ^Any index ^UInt]
            (if (!= index (__NATIVE_LIST_SIZE__ array))
                (next (func value (array index)) (__NATIVE_NUMBER_ADD__ index 1))
                value))
                (array 0) 1)
    [array ^Indexed value ^Any func ^Function]
        ((fn next [value ^Any index ^UInt]
            (if (!= index (__NATIVE_LIST_SIZE__ array))
                (next (func value (array index)) (__NATIVE_NUMBER_ADD__ index 1))
                value))
                value 0))

(defn list [... values] ^List
    (let [this (__NATIVE_CREATE_LIST_FROM_VECTOR__ values)]
        (fn list [index ^UInt]
            (if (!= index nil) (__NATIVE_LIST_GET__ this index) this))))

(defn +
    ([] ^Number 0)
    ([x ^Number] ^Number x)
    ([x ^Number y ^Number] ^Number (__CREATE_NUMBER_ADD__ [x y]))
    ([x ^Number y ^Number ... args ^Vector<Number>] ^Number (simple-reduce args (+ x y) +)))
