(define (iterative-improve good-enough? improve)
  (define (iter guess)
    (if (good-enough? guess)
      guess
      (iter (improve guess))))

  iter)

(define (average x y) (/ (+ x y) 2))
(define (make-improve x) (lambda (guess) (average guess (/ x guess))))

(define (make-good-enough? x)
  (lambda (guess) (< (abs (- (square guess) x)) 0.001)))

(define (square x) (* x x))

(define (sqrt x)
  ((iterative-improve (make-good-enough? x) (make-improve x)) x))
