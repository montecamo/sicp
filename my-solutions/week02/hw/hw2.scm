(define (every f sen)
  (if (empty? sen)
     '()
     (se (f (first sen)) (every f (bf sen)))))
