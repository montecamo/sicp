(define (repeated f count)
  (if (<= count 1)
    f
    (compose f (repeated f (- count 1)))))

(define (compose f g)
  (lambda (x) (f (g x))))
