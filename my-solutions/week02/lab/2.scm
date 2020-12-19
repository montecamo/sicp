(define (substitute sen target new)
  (define (replace wd)
    (if (equal? wd target)
        new
        wd))

  (if (empty? sen)
      '()
      (se (replace (first sen)) (substitute (bf sen) target new))))

