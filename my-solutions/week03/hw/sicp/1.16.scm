(define (fast-expt b n)
  (define (fast-expt-iter b n a)
    (cond ((= n 0) a)
          ((even? n) (fast-expt-iter (square b) (half n) a))
          (else (fast-expt-iter b (- n 1) (* a b)))))
  (fast-expt-iter b n 1))

(define (even? n)
  (= (remainder n 2) 0))

(define (square x)
  (* x x))

(define (half x)
  (/ x 2))
