(define make-rect cons)

(define width car)
(define height cdr)

(define (double x)
  (* x 2))

(define (perimeter rect)
  (+ (double (width rect)) (double (height rect))))

(define (area rect)
  (* (width rect) (height rect)))


; custom implementation
(define (make-rect width height)
  (lambda (t) (cond ((= t 0) width)
                    ((= t 1) height))))

(define (width rect)
  (rect 0))

(define (height rect)
  (rect 1))

(define (double x)
  (* x 2))

(define (perimeter rect)
  (+ (double (width rect)) (double (height rect))))

(define (area rect)
  (* (width rect) (height rect)))


