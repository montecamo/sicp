(define (lookup keys table)
  (let ((record (assoc (car keys) (cdr table))))
    (cond ((and (null? (cdr keys)) record) (cdr record))
          ((not record) false)
          (else (lookup (cdr keys) record)))))

(define (insert! keys value table) 
  (let ((record (assoc (car keys) (cdr table))))
    (cond ((and (null? (cdr keys)) record) (set-cdr! record value))
          ((and (not record) (not (null? (cdr keys))))
           (begin (set-cdr! table
                            (cons (list (car keys)
                                        (cons (car keys) value))
                                  (cdr table)))
                  (insert! keys value table)))
          ((and (null? (cdr keys)) (not record)) (set-cdr! table
                                                           (cons (cons (car keys) value)
                                                                 (cdr table))))
          (else (insert! (cdr keys) value record)))))
