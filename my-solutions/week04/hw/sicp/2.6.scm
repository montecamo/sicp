(define (compose f g)
  (lambda (x) (f (g x))))

(define (try num)                       ; convert Church to
  ((num (lambda (x) (+ x 1))) 0))       ; ordinary number

(define zero (lambda (f) (lambda (x) x)))
(define one (lambda (f) (lambda (x) (f x))))
(define two (lambda (f) (lambda (x) (f (f x)))))
(define three (lambda (f) (lambda (x) (f (f (f x))))))

(define (add first second)
  (lambda (f) (lambda (x) ((first f) ((second f) x)))))

(define (mul first second)
  (lambda (f) (first (second f))))

(define (exp base n)
  ((n (lambda (y) (mul base y))) one))


(define (sub first second)
  (lambda (f) (lambda (x) ((car ((second cdr) ((first (lambda (y) (cons (compose f (car y)) y))) (cons (lambda (x) x) nil)))) x))))
