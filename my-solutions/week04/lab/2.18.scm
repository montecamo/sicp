(define (reverse l)
  (if (null? l)
    nil
    (append (reverse (cdr l)) (list (car l)))))
