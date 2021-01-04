(define make-segment cons)

(define start-segment car)
(define end-segment cdr)

(define make-point cons)

(define x-point car)
(define y-point cdr)

(define (average x y)
  (/ (+ x y) 2))

(define (midpoint-segment s)
  (make-point (average (x-point (start-segment s)) (x-point (end-segment s)))
              (average (y-point (start-segment s)) (y-point (end-segment s)))))

(define (print-point p) (newline)
  (display "(") (display (x-point p)) (display ",")
  (display (y-point p))
  (display ")"))

