(define (make-safe f pred?)
  (lambda (x) (if (pred? x) (f x) #f)))

(define (number? x) #f)

(define (square x) (* x x))

(define safe-square (make-safe square number?))
