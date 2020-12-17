(define (biggest-sum x y z)
  (- (squares-sum x y z) (square (min x y z))))

(define (squares-sum x y z)
  (+ (square x) (square y) (square z)))

(define (square x)
  (* x x))
