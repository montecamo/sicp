; Here is how to do ALARM and ALARM-INTERRUPT in STk with our
; Berkeley modifications. (Apr. 26, 2000 - brg)

(define x 42)
(define (alarm-interrupt) (set! x 69))
(define (alarm-signal-handler sig) (alarm-interrupt))
(define (printx-loop n) (or (> n 25000) (begin (display "x is ") (display x) (display ", iteration#") (display n) (newline) (printx-loop (+ n 1)))))
(add-signal-handler! 14 alarm-signal-handler)
(alarm 5)
(printx-loop 0)
