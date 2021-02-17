(define (make-account balance password) 
  ((lambda (incorrect-attempts passwords)
    (define (withdraw amount)
      (if (>= balance amount)
        (begin (set! balance (- balance amount)) balance)
        "Insufficient funds"))
    (define (deposit amount)
      (set! balance (+ balance amount))
      balance)
    (define (valid-password? pass) (member? pass passwords))
    (define (add-password pass) (set! passwords (cons pass passwords)))
    (define (incorrect-password . args) 
      (if (>= incorrect-attempts 2) 
        (call-cops)
        (begin (set! incorrect-attempts (+ incorrect-attempts 1)) "Incorrect password")))

    (define (protected-dispatch m)
      (begin 
        (set! incorrect-attempts 0)
        (cond ((eq? m 'withdraw) withdraw)
              ((eq? m 'deposit) deposit)
              ((eq? m 'add-password) add-password)
              (else (error "Unknown request: MAKE-ACCOUNT"
                           m)))))

    (define (call-cops) "I'm calling cops, fucking thief")

    (define (dispatch pass m)
      (cond ((not (valid-password? pass)) incorrect-password)
            (else (protected-dispatch m))))

    dispatch)
   0 (list password)))

(define (make-joint acc old-pass new-pass)
  (begin ((acc old-pass 'add-password) new-pass) acc))
