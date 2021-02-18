(define (vowel? letter)
  (member? letter '(a e i o u)))

(define (len sen)
  (if (empty? sen) 0 (+ 1 (len (butfirst sen)))))

(define (replace-vowel-reps sen)
  (define (helper sen filtered prev)
    (cond ((empty? sen) filtered)
          ((and (vowel? prev) (vowel? (first sen))) (helper (butfirst sen) filtered prev))
          (else (helper (butfirst sen) (word filtered (first sen)) (first sen)))))
  
  (helper (butfirst sen) (first sen) (first sen)))

(define (syllables sen)
  (len (keep (lambda (x) (vowel? x)) (replace-vowel-reps sen))))
