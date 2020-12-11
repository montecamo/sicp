; Here is how to do ALARM and ALARM-INTERRUPT in STk with our
; Berkeley modifications. (Apr. 26, 2000 - brg)

(define (alarm-interrupt) (error "Ring!"))
(define (alarm-signal-handler sig) (alarm-interrupt))
(add-signal-handler! 14 alarm-signal-handler)
(alarm 10)

