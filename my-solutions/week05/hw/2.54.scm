(define (symbol? x)
  (not (pair? x)))

(define (equal? first second)
  (cond ((and (null? first) (null? second)) #t)
        ((and (symbol? first) (symbol? second)) (eqv? first second))
        ((and (pair? first) (pair? second))
         (and (equal? (car first) (car second)) (equal? (cdr first) (cdr second))))
        (else #f)))
