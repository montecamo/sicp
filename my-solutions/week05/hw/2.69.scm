(define (generate-huffman-tree pairs)
  (successive-merge (make-leaf-set pairs)))


(define (successive-merge trees)
  (if (= (length trees) 1)
    (car trees)
    (successive-merge (adjoin-set (make-code-tree (car trees) (cadr trees)) (cddr trees)))))
    
