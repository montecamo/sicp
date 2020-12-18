(define (squares sen)
  (if (empty? sen)
      '()
      (sentence (square (first sen)) (squares (bf sen)))
      ))

(define (square x)
  (* x x))

