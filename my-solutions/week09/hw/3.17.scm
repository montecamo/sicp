(define (count-pairs x)
  (define (helper y flag)
    (cond ((not (pair? y)) 0)
          (else (let ((result (+ (helper (car y) #t) (helper (cdr y) #f))))
                  (if (not flag)
                    result
                    (+ result 1))))))
  (helper x #t))
