(define (cons x y) (lambda (m) (m x y)))

(define (car z)
  (z (lambda (p q) p)))

(define (cdr z)
  (z (lambda (p q) q)))

(define (test-car)
  (define t (cons (lambda () (newline) (display "works"))
                  (lambda () (newline) (display "failed"))))

  ((car t)))

(define (test-cdr)
  (define t (cons (lambda () (newline) (display "failed"))
                  (lambda () (newline) (display "works"))))

  ((cdr t)))

