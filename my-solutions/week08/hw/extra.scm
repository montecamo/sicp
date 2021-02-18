(define make-namer (lambda () (let ((count 0)) (lambda () (set! count (+ count 1)) (word 'g count)))))

(define (lookup frame key)
  (cond ((null? frame) key)
        ((eq? (caar frame) key) (cadar frame))
        (else (lookup (cdr frame) key))))

(define (make-bounder) 
  (define new-name (make-namer))
  (lambda (frame vars)
    (append (map (lambda (var) (list var (new-name))) vars) (filter (lambda (x) (not (member? (car x) vars))) frame))))

(define (lambda-exp? exp)
  (and (pair? exp) (eq? (car exp) 'lambda)))

(define lambda-args cadr)
(define lambda-body caddr)


(define (unique-rename exp)
  (define bound (make-bounder))
  (define (substitute exp frame)
    (cond ((lambda-exp? exp)
           (let ((new-frame (bound frame (lambda-args exp))))
             (list 
               'lambda
               (map (lambda (x) (lookup new-frame x)) (lambda-args exp))
               (substitute (lambda-body exp) new-frame))))
          ((symbol? exp) (lookup frame exp))
          ((number? exp) exp)
          (else (map (lambda (x) (substitute x frame)) exp))))
  (substitute exp '()))

