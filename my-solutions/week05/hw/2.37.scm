(define (dot-product v w)
  (accumulate + 0 (map * v w)))

(define (matrix-*-vector m v)
  (map (lambda (x) (dot-product x v)) m))

(define (transpose mat) 
  (accumulate-n cons nil mat))

(define (matrix-*-matrix m n) 
  (let ((cols (transpose n)))
    (map (lambda (v1) (map (lambda (v2) (dot-product v1 v2)) cols)) m)))
