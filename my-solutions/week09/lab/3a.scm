(define list1 (list (list 'a) 'b))
(define list2 (list (list 'x) 'y))

(set-cdr! (car list2) (cadr list1))
(set-cdr! (car list1) (car list2))
