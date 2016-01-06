
(if test then else?)

(do exprs*)

(let [bindings*] exprs*)

(quote form)

(def symbol init?)

(fn name? [params*] exprs*)

(macro name? [params*] exprs*)

(def defmarco
    (macro defmarco
        [name params ... exprs]
            (list (quote def) name ((quote macro) name params exprs))))

(def list
    (fn list [... values]
        (. lisp.lang.List.from_vector values)))

(defmarco defn [name params ... exprs]
    (list (quote def) name ((quote fn) name params exprs)))
