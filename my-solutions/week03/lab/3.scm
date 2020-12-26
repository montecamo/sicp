(define (count-change amount) (cc amount '(5 1)))

(define (cc amount kinds-of-coins)
  (cond ((= amount 0) 1)
        ((or (< amount 0) (empty? kinds-of-coins)) 0)
        (else (+ (cc amount (bf kinds-of-coins))
                 (cc (- amount (first kinds-of-coins))
                     kinds-of-coins)))))
