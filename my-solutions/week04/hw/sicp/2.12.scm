(define (calc-percent num percent)
  (/ (* num percent) 100))

(define (get-percent main part)
  (/ (* part 100) main))


(define (center i)
  (/ (+ (lower-bound i) (upper-bound i)) 2))
(define (width i)
  (/ (- (upper-bound i) (lower-bound i)) 2))


(define (make-center-percent c p)
  (make-interval (- c (calc-percent c p)) (+ c (calc-percent c p))))

(define (percent i)
  (get-percent (center i) (width i)))
