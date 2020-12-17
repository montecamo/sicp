(define (plural wd)
  (word wd 's))

(define (plural wd)
  (cond ((and (equal? (last wd) 'y) (vowel? (last (bl wd)))) (word wd 's))
        ((equal? (last wd) 'y) (word (bl wd) 'ies))
        (else (word wd 's))))

(define (vowel? letter)
  (member? letter 'aeiou))

