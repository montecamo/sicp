;; Scheme calculator -- evaluate simple expressions

; The read-eval-print loop:

(define (calc)
  (display "calc: ")
  (flush)
  (print (calc-eval (read)))
  (calc))

; Evaluate an expression:

(define (calc-eval exp)
  (cond ((number? exp) exp)
        ((word? exp) exp)
        ((list? exp) (calc-apply (car exp) (map calc-eval (cdr exp))))
        (else (error "Calc: bad expression:" exp))))

; Apply a function to arguments:

(define (calc-apply fn args)
  (cond ((eq? fn '+) (accumulate + 0 args))
        ((eq? fn '-) (cond ((null? args) (error "Calc: no args to -"))
                           ((= (length args) 1) (- (car args)))
                           (else (- (car args) (accumulate + 0 (cdr args))))))
        ((eq? fn '*) (accumulate * 1 args))
        ((eq? fn '/) (cond ((null? args) (error "Calc: no args to /"))
                           ((= (length args) 1) (/ (car args)))
                           (else (/ (car args) (accumulate * 1 (cdr args))))))
        ((eq? fn 'first) (if (> (length args) 1) 
                           (error "Calc: too many args for first")
                           (first (car args))))
        ((eq? fn 'butfirst) (if (> (length args) 1) 
                           (error "Calc: too many args for butfirst")
                           (butfirst (car args))))
        ((eq? fn 'last) (if (> (length args) 1) 
                           (error "Calc: too many args for last")
                           (last (car args))))
        ((eq? fn 'butlast) (if (> (length args) 1) 
                           (error "Calc: too many args for butlast")
                           (butlast (car args))))
        ((eq? fn 'word) (accumulate word "" args))

        (else (error "Calc: bad operator:" fn))))

