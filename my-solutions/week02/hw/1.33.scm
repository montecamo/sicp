(define (filtered-accumulate pred combiner null-value term a next b)
  (cond ((> a b) null-value)
        ((pred (term a)) 
         (combiner (term a)
                   (accumulate pred combiner null-value term (next a) next b)))
        (else (accumulate pred combiner null-value term (next a) next b))))

(define (sum-squares a b)
  (filtered-accumulate prime? + 0 square a inc b))

