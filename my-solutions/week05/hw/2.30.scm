(define (square x)
  (* x x))

(define (square-tree tree)
  (cond ((empty? tree) nil)
        ((not (pair? tree)) (square tree))
        (else (cons (square-tree (car tree)) (square-tree (cdr tree))))))


(define (square-tree-2 tree)
  (map (lambda (x) (if (pair? x) (square-tree-2 x) (square x))) tree))
