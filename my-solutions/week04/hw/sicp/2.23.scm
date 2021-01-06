(define (for-each func l)
  (and (not (null? l)) (func (car l)))
  (and (not (null? l)) (for-each func (cdr l))))

