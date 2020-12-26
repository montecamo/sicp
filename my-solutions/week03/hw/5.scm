(define (number-of-partitions n) (helper n n))

(define (helper n product)
  (cond 
    ((or (< n 0) (= product 0)) 0)
    ((= n 0) 1)
    (else (+ (helper n (- product 1))                          
             (helper (- n product) product)))))
