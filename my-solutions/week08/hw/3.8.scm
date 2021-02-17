(define f (let ((val 0))
            (lambda (x) (let ((mem val))
                          (begin (set! val x) mem)))))
