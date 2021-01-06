(define (replace word olds news)
  (cond ((null? olds) word)
        ((equal? word (car olds)) (car news))
        (else (replace word (cdr olds) (cdr news)))))

(define (substitute2 l olds news)
  (cond ((null? l) nil)
        ((list? (car l)) (cons (substitute2 (car l) olds news) (substitute2 (cdr l) olds news)))
        (else (cons (replace (car l) olds news) (substitute2 (cdr l) olds news)))))
