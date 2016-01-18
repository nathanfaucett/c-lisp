; define def macro
(def defmacro (macro defmacro [input]
    (list (quote def) (list-get input 1)
        ((quote macro) (list-get input 1) (list-get input 2) (list-get input 3))))))

; define def function
(defmacro defn [input]
    (list (quote def) (list-get input 1)
        ((quote fn) (list-get input 1) (list-get input 2) (list-get input 3))))

(defn fac [x]
    (if (= x 1) x
        (* x (fac (- x 1)))))

(fac 5)
