(define (e k)
  (+ 2 (cont-frac (lambda (x) 1) (lambda (x) (if (= (remainder x 3) 2) (* (/ (+ x 1) 3) 2) 1)) k)))
