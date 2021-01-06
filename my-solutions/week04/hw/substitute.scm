(define (substitute l old new)
  (cond ((null? l) nil)
        ((list? (car l)) (cons (substitute (car l) old new) (substitute (cdr l) old new)))
        ((equal? (car l) old) (cons new (substitute (cdr l) old new)))
        (else (cons (car l) (substitute (cdr l) old new)))))

