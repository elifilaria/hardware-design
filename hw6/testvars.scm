(define addn
  (lambda (x)
    (define n 7)
    (+ x n)))
(display "enter an integer value: ")
(define val (read))
(display "The call addn(")
(display val)
(display ") returns ")
(display (addn val))
(newline)