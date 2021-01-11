
(define (make-mobile left right) (cons left right))
(define (make-branch length structure) (cons length structure))

(define left-branch car)
(define right-branch cdr)

(define branch-length car)
(define branch-structure cdr)

(define (total-weight mobile)
  (if (pair? mobile)
    (+ (total-weight (branch-structure (left-branch mobile)))
       (total-weight (branch-structure (right-branch mobile))))
    mobile))

(define (balanced? mobile)
  (if (pair? mobile) 
    (let ((left (left-branch mobile)) (right (right-branch mobile)))
      (and (= (* (branch-length left) (total-weight (branch-structure left)))
              (* (branch-length right) (total-weight (branch-structure right))))
           (balanced? (branch-structure left))
           (balanced? (branch-structure right))))
    #t))
