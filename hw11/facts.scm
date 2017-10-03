(define print-sums (lambda (n)
		     (sum-squares (n))))

(define sum-squares (lambda (n)
		      (cond
		       ((= n 1) 1)
		       (else
			(+ (* n n) (sum-squares (- n 1)))))))
(newline)
(display (sum-squares 3))
(newline)
