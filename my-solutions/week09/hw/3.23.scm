(define (value v) (vector-ref v 0))
(define (prev v) (vector-ref v 1))
(define (next v) (vector-ref v 2))

(define (set-prev! node new-node) (vector-set! node 1 new-node))
(define (set-next! node new-node) (vector-set! node 2 new-node))
(define (link-nodes! prev next) (begin (set-prev! next prev) (set-next! prev next)))

(define (make-node value prev next) (vector value prev next))



(define (front-ptr deque) (car deque))
(define (rear-ptr deque) (cdr deque))

(define (set-front-ptr! deque item)
  (set-car! deque item))
(define (set-rear-ptr! deque item)
  (set-cdr! deque item))

(define (empty-deque? deque) 
  (or (null? (front-ptr deque)) (null? (rear-ptr deque))))
(define (make-deque) (cons '() '()))


(define (front-deque deque) (value (front-ptr deque)))
(define (rear-deque deque) (value (rear-ptr deque)))

(define (front-insert-deque! deque item)
  (let ((new-node (make-node item nil nil)))
    (cond ((empty-deque? deque) (set-front-ptr! deque new-node) (set-rear-ptr! deque new-node) deque)
          (else
            (begin (link-nodes! new-node (front-ptr deque)) (set-front-ptr! deque new-node) 'okay)))))

(define (rear-insert-deque! deque item)
  (let ((new-node (make-node item nil nil)))
    (cond ((empty-deque? deque) (set-front-ptr! deque new-node) (set-rear-ptr! deque new-node) deque)
          (else
            (begin (link-nodes! (rear-ptr deque) new-node) (set-rear-ptr! deque new-node) 'okay)))))

(define (front-delete-deque! deque) 
  (cond ((empty-deque? deque) (error "DELETE! called with an empty deque" deque))
        (else (begin (set-front-ptr! deque (next (front-ptr deque))) 'okay))))

(define (rear-delete-deque! deque) 
  (cond ((empty-deque? deque) (error "DELETE! called with an empty deque" deque))
        (else (begin (set-rear-ptr! deque (prev (rear-ptr deque))) 'okay))))

