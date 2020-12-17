(define (dupls-remover str result)
  (cond ((empty? str) result)
        ((member? (first str) (bf str)) (dupls-remover (bf str) result))
        (else (dupls-remover (bf str) (word result (first str))))))

(define (dupls-removed str)
  (dupls-remover str ""))
