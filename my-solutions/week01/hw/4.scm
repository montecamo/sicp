(define (ordered? sen)
  (cond ((or (empty? sen) (empty? (bf sen))) #t)
        ((< (first sen) (first (bf sen))) (ordered? (bf sen)))
        (else #f)))
