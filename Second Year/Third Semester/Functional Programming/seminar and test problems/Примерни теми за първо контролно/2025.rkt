#lang racket


; problem 1

(define (digits n) (cond ((zero? n) 1)
                         ((< n 10) 1)
                         (else (+ 1 (digits (quotient n 10))))))

(define (multiply-by-position n)
  (define (iter num pos) (cond ((< num 10) (* num pos))
                               (else (+ (* (iter (quotient num 10) (+ pos 1)) (expt 10 (digits (* (remainder num 10) pos)))) (* (remainder num 10) pos)))))
  (iter n 1))
                                       

;(displayln (multiply-by-position 123)) ; → 1*3, 2*2, 3*1 → 343
;(displayln (multiply-by-position 507)) ; → 5*3, 0*2, 7*1 → 1507
;(displayln (multiply-by-position 987)) ; → 9*3, 8*2, 7*1 → 27167
;(displayln (multiply-by-position 1249)); → 1*4, 2*3, 4*2, 9*1 → 4689
;(displayln (multiply-by-position 9000)); → 9*4, 0*3, 0*2, 0*1 → 36000


; problem 2

(define (square x) (* x x))
(define (1+ x) (+ x 1))

(define (minmax fm l) (apply min (map (lambda (row) (apply max (map (lambda (f) (apply max (map f l))) row))) fm)))

  
;(displayln (minmax (list (list square exp) (list cos 1+)) '(-1 0 1))) ; -> 2.0



; problem 3

(define t1 '(1 (4 () ())
              (6 (3 () ())
                 (-4 () ())
              )
           )
  )

(define t2 '(1 (4 () ()) (6 (-2 () ()) (-4 () ()))))

(define (sum-even lst) (cond ((null? lst) 0)
                             ((zero? (remainder (car lst) 2)) (+ (car lst) (sum-even (cdr lst))))
                             (else (sum-even (cdr lst)))))


(define (maximum-even-nodes-sum t)
  (define (iter curr tree) (let ((currNew (append curr (list (car tree)))))
                             (cond ((and (null? (cadr tree)) (null? (caddr tree))) (list currNew)) 
                                   (else (append (list currNew) (iter (append curr (list (car tree))) (cadr tree)) (iter  (append curr (list (car tree))) (caddr tree)))))))
  (foldl (lambda (acc curr) (cond ((> (sum-even acc) (sum-even curr)) acc)
                                   ((< (sum-even acc) (sum-even curr)) curr)
                                   (else (if (> (length acc) (length curr)) acc curr)))) (car (iter `() t)) (iter `() t)))
  

;(displayln (maximum-even-nodes-sum '(1 (4 () ()) (6 (3 () ()) (-4 () ())))))  ; -> (1 6 3)
;(displayln (maximum-even-nodes-sum '(1 (4 () ()) (6 (-2 () ()) (-4 () ()))))) ; -> (1 6)

