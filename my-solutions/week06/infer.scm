
(define (infer proc) (
  (define (helper exp types) (
    (cond ((quote-exp? exp) (add-types types (map (lambda (arg) (make-type arg '?)) (cdr exp))))
          ((map-exp? exp) (add-types types (list (make-type (cadr exp) 'procedure) (make-type (caddr exp) 'list))))
          ((every-exp? exp) (add-types types (list (make-type (cadr exp) 'procedure) (make-type (caddr exp) 'sentence-or-word))))
          ((or (+-exp? exp) (--exp? exp) (max-exp? exp) (min-exp? exp)) (add-types types (map (lambda (arg) (make-type arg 'number)) (cdr exp))))
          ()


(define (add-types types new-types)
  (if (null? new-types)
      types
      (add-types (add-type types (car new-types)) (cdr new-types))))

(define (add-type types type) 
  (cond ((null? types) (list type))
        (else (let (
          (first-arg (type-arg (car types)))
          (second-arg (type-arg type))
          (first-type (type-type (car types)))
          (second-type (type-type type)))
          (cond ((and (eq? first-arg second-arg) (eq? first-type second-type)) types)
                ((and (eq? first-arg second-arg) (eq? second-type '?)) types)
                ((and (eq? first-arg second-arg) (eq? first-type '?)) (cons (make-type second-arg second-type) (cdr types)))
                ((eq? first-arg second-arg) (cons (make-type first-arg 'x) (cdr types)))
                (else (cons (car types) (add-type (cdr types) type))))))))

(define type-arg car)
(define type-type cadr)
(define make-type list)

(define (map-exp-args))
(define exp-args cadr)
(define (proc-args proc) 
  (cdr (cadr proc)))

(define (proc-body proc)
  (caddr proc))

(define (exp-checker type)
  (lambda (exp) (and (pair? exp) (eq? (car exp) type))))

(define quote-exp? (exp-checker 'quote))
(define map-exp? (exp-checker 'map))
(define every-exp? (exp-checker 'every))
(define +-exp? (exp-checker '+))
(define --exp? (exp-checker '-))
(define max-exp? (exp-checker 'max))
(define min-exp? (exp-checker 'min))
(define append-exp? (exp-checker 'append))
(define member-exp? (exp-checker 'member))
(define first-exp? (exp-checker 'first))
(define butfirst-exp? (exp-checker 'butfirst))
(define member?-exp? (exp-checker 'member?))
(define sentence-exp? (exp-checker 'sentence))

;'(define (foo a b c d e f) (f (append (a b) c '(b c)) (+ 5 d) (sentence (first e) f)) )