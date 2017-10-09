(define factorial
  (lambda (num) ; a non-negative integer
    (if (= 0 num) 1
	;; assert:  num > 0
	(* num (factorial (- num 1))))))

(factorial 10)
(define fact (factorial 10))
(if (= fact 3628800) (display "correct! \n") (display "incorrect! \n"))

(define x 17)
(if (number? x) (display "number \n") (display "non-number \n"))

(define y "cat")
(if (number? y) (+ y 1 "\n") (display y))

(newline)

(define z 17)
(if (number? z) (+ z 1) (display z))
