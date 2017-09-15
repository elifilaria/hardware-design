;;; print factorials in Scheme language.  R. Brown, 9/2010

(define factorial
  (lambda (n)
     (if (< n 1) 1
        (* n (factorial (- n 1))))))
 
(define print-facts
  (lambda (n) ; print factorials from n to 5
    (if (>  n 5) 'done
	(begin
	  (display n)
	  (display "\t")
	  (display (factorial n))
	  (newline)
	  (print-facts (+ n 1))))))

(display "n\t(n!)")
(newline)
(display "------------------")
(newline)
(print-facts 0)

