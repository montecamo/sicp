(define (twenty-one strategy)
  (define (play-dealer customer-hand dealer-hand-so-far rest-of-deck)
    (cond ((> (best-total dealer-hand-so-far) 21) 1)
          ((< (best-total dealer-hand-so-far) 17)
           (play-dealer customer-hand
                        (se dealer-hand-so-far (first rest-of-deck))
                        (bf rest-of-deck)))
          ((< (best-total customer-hand) (best-total dealer-hand-so-far)) -1)
          ((= (best-total customer-hand) (best-total dealer-hand-so-far)) 0)
          (else 1)))

  (define (play-customer customer-hand-so-far dealer-up-card rest-of-deck)
    (cond ((> (best-total customer-hand-so-far) 21) -1)
          ((strategy customer-hand-so-far dealer-up-card)
           (play-customer (se customer-hand-so-far (first rest-of-deck))
                          dealer-up-card
                          (bf rest-of-deck)))
          (else
            (play-dealer customer-hand-so-far
                         (se dealer-up-card (first rest-of-deck))
                         (bf rest-of-deck)))))

  (let ((deck (make-deck)))
    (play-customer (se (first deck) (first (bf deck)))
                   (first (bf (bf deck)))
                   (bf (bf (bf deck))))) )

(define (make-ordered-deck)
  (define (make-suit s)
    (every (lambda (rank) (word rank s)) '(A 2 3 4 5 6 7 8 9 10 J Q K)) )
  (se (make-suit 'H) (make-suit 'S) (make-suit 'D) (make-suit 'C)) )

(define (make-deck)
  (define (shuffle deck size)
    (define (move-card in out which)
      (if (= which 0)
        (se (first in) (shuffle (se (bf in) out) (- size 1)))
        (move-card (bf in) (se (first in) out) (- which 1)) ))
    (if (= size 0)
      deck
      (move-card deck '() (random size)) ))
  (shuffle (make-ordered-deck) 52) )

(define (picture-card? card)
  (member? (first card) '(j q k)))
(define (ace-card? card)
  (equal? (first card) 'a))

(define (get-card-value card big-ace?)
  (cond ((and (ace-card? card) big-ace?) 11)
        ((ace-card? card) 1)
        ((picture-card? card) 10)
        (else (bl card))))

(define (best-total hand)
  (define (helper total hand)
    (cond ((> total 21) -1)
          ((empty? hand) total)
          (else (max (helper (+ total (get-card-value (first hand) #t)) (bf hand))
                     (helper (+ total (get-card-value (first hand) #f)) (bf hand))))))
  (let ((result (helper 0 hand)))
    (if (= result -1) 22 result)))


(define (stop-at-17 hand dealers-card)
  (if (< (best-total hand) 17) #t #f))

(define (play-n strategy n)
  (if (<= n 0)
    0
    (+ (twenty-one strategy) (play-n strategy (- n 1)))))

(define (dealer-sensitive hand dealers-card)
  (or (and (or (ace-card? dealers-card) (picture-card? dealers-card) (member? (bl dealers-card) '(7 8 9 10)))
           (< (best-total hand) 17))
      (and (member? (bl dealers-card) '(2 3 4 5 6)) (< (best-total hand) 12))))

(define (stop-at n)
  (lambda (hand dealers-card) (< (best-total hand) n)))




