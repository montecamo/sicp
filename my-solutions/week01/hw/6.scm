(define (and-special-form?)
  (define x 1)
  (define (change)
    (set! x 0))
  (and #f (change))
  (if (= x 1) '(special and) '(ordinary and)))

(define (or-special-form?)
  (define x 1)
  (define (change)
    (set! x 0))
  (or #t (change))
  (if (= x 1) '(special or) '(ordinary or)))

