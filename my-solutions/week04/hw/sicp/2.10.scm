(define (make-interval a b) 
  (cond ((and (<= a 0) (>= b 0)) error "Spans zero")
        ((and (<= b 0) (>= a 0)) error "Spans zero")
        (else (cons a b))))

