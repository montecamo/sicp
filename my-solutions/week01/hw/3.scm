(define (switch sen)
  (if (equal? (first sen) 'you)
      (sentence 'i (switch-body (bf sen)))
      (switch-body sen)))

(define (switch-body sen)
  (if (empty? sen)
      '()
      (sentence (replace (first sen)) (switch-body (bf sen)))))

(define (replace wd)
  (cond ((or (equal? wd 'i) (equal? wd 'me)) 'you)
        ((equal? wd 'you) 'me)
        (else wd)))
