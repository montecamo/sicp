(define (number-of-partitions n) 
  (iter n n 0 (lambda (count) count)))

(define (iter n chunk count up)
  (cond 
    ((or (< n 0) (= chunk 0)) (up count ))
    ((= n 0) (up (+ count 1)))
    (else (iter n (- chunk 1) count (lambda (c) (iter (- n chunk) chunk c up))))))
