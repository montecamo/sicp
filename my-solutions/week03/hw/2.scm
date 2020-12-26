
(define (next-perf n)
  (if (equal? (sum-of-factors n) n) n (next-perf (+ n 1))))

(define (sum-of-factors n)
  (define (sum-of-factors-helper num)
    (cond ((< num 1) 0)
          ((equal? (remainder n num) 0) (+ num (sum-of-factors-helper (- num 1))))
          (else (sum-of-factors-helper (- num 1)))))
  (sum-of-factors-helper (- n 1)))
