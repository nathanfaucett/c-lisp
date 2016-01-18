(def defmacro (macro defmacro [input]
    (list (quote def) (list-get input 1)
        ((quote macro) (list-get input 1) (list-get input 2) (list-get input 3))))))

(def return (fn return [... args]
    (let [a 1 b 2]
        (do
            (swap a b) args))))

(return 1 2 3)
