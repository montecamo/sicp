(define (reverse l)
  (cond ((null? l) nil)
        ((not (pair? l)) l)
        (else (append (reverse (cdr l)) (list (reverse (car l)))))))
