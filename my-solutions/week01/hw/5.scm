(define (ends-e sen)
  (if (empty? sen)
      '()
      (sentence (replace-not-ends-e (first sen)) (ends-e (bf sen)))))

(define (replace-not-ends-e wd)
  (if (equal? (last wd) 'e) wd '()))
