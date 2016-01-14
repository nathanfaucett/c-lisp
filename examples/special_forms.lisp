; type defaults to Any
(def symbol ^Type? init?)
; (def PI ^Float32 3.14159265359)
; (def PI 3.14159265359) Type is Any

; type defaults to Any
(swap symbol ^Type? init?)
; (def x 1)
; (swap x 2)

; special forms, returns nil if else case and no else provided
(if test then else?)

; returns last exprs
(do exprs*)

(let [bindings*] exprs*)
; (let [var value] (body-that-uses var))
; (let [number ^Int 1] (+ number 1))

; returns uninterrupted first argument
(quote form)

; return type defaults to Any
(fn name? [params*] ^ReturnType? exprs*)
; (fn name? [params*] expr)
; (fn name? [params*] expr_1 expr_2 ... expr_n)
; (fn name? [params*] [expr_1 expr_2 ... expr_n])

; return type defaults to Any
(macro name? [params*] ^ReturnType? exprs*)
; (macro name? [params*] expr)
; (macro name? [params*] expr_1 exp_2 ... expr_n)
; (macro name? [params*] [expr_1 expr_2 ... expr_n])

(try expr catch-clause finally-clause?)
; catch and finally symbols injected in try scope
; (try (/ 1 0)
;    (catch [e : Exception]
;        (some-print-function e))
;    (finally (some-function ... args)))

(throw expr)

; Template optional, Parent defaults Any
(struct TypeName Template? [members*] ^Parent?)
; (struct SomeType
;    <Type ^Any OtherType ^Any> [a ^Type b ^OtherType] Index)
; (struct Counter [count ^Int])


; examples

(def != (fn != [a ^Any b ^Any] ^Boolean
    (__NATIVE_NOT_EQUAL__ a b)))

(def defmacro
    (macro defmacro
        [... args] ^List
            (list args))

(defmacro defn [... args] ^List (list args))
