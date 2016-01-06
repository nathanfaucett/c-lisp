;; call c++ module
(. symbol-to-function-set-in-c++ ...args)

(defn ! [value]
    (. lisp.lang.not value))

(defn !! [value]
    (. lisp.lang.Boolean.cast value))

(defn == [a b]
    (. lisp.lang.equals a b))

(defn != [a b]
    (! (== a b)))

(defn simple-reduce
    [array func]
        ((fn next [value index]
            (if (!= index (. lisp.lang.List.size array))
                (next (func value (. lisp.lang.List.get array index)) (. lisp.lang.Number.add [index 1]))
                value))
                (. lisp.lang.List.get array 0) 1)
    [array value func]
        ((fn next [value index]
            (if (!= index (. lisp.lang.List.size array))
                (next (func value (. lisp.lang.List.get array index)) (. lisp.lang.Number.add [index 1]))
                value))
                value 0))

(defn +
    ([] 0)
    ([x] (. lisp.lang.Number.cast x))
    ([x y] (. lisp.lang.Number.add [x y]))
    ([x y ... args] (simple-reduce args (+ x y) +)))
