(define (type-check f predicate? x)
  (if (predicate? x) (f x) #f))
