(define (filter pred l)
  (cond ((null? l) nil)
        ((pred (car l)) (cons (car l) (filter pred (cdr l))))
        (else (filter pred (cdr l)))))

(define (even? x)
  (= (remainder x 2) 0))

(define (odd? x)
  (= (remainder x 2) 1))

(define (same-parity . rest)
  (if (even? (car rest))
    (filter even? rest)
    (filter odd? rest)))
