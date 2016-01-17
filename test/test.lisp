(def return (fn return [x y]
    (do (swap x y) x)))

(return 1 2)
