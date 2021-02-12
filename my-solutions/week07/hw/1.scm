(define-class (random-generator border)
  (instance-vars (count 0))
  (method (number) (set! count (+ count 1)) (random border)))

