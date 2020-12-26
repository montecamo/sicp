(define (cont-frac n d k)
  (define (cont-frac-rec n d count)
    (if (= count k)
      (/ (n count) (d count))
      (/ (n count) (+ (d count) (cont-frac-rec n d (+ count 1))))))

  (cont-frac-rec n d 1))

(define (cont-frac-iterative n d k)
  (define (cont-frac-iter n d k result)
    (if (= k 0)
      result 
      (cont-frac-iter n d (- k 1) (/ (n k) (+ (d k) result)))))
  (cont-frac-iter n d (- k 1) (/ (n k) (d k))))

