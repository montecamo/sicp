(define (make-time hr mn cat) (list hr mn cat))
(define hour car)
(define minute cadr)
(define category caddr)

(define (time-print-form time)
  (word (hour time) ': (minute time) (category time)))

(define (24-hour time)
  (if (eq? (category time) 'am)
    (word (hour time) (minute time))
    (word (+ (hour time) 12) (minute time))))
