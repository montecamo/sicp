(define (square x)
  (* x x))

(define (square-map func tree)
  (cond ((empty? tree) nil)
        ((not (pair? tree)) (func tree))
        (else (cons (square-tree (car tree)) (square-tree (cdr tree))))))

(define (square-tree tree)
  (square-map square tree))
