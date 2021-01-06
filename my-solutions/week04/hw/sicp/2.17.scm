(define (last-pair l)
  (if (empty? (cdr l)) (car l) (last-pair (cdr l)))) 
