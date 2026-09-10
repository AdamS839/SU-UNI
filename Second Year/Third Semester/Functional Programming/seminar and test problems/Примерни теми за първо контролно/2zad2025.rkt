#lang racket

(define (deepMapCond lst p? f1 f2)
  (define (iter lst d) (cond ((null? lst) `())
                             ((list? (car lst)) (cons (iter (car lst) (+ d 1)) (iter (cdr lst) d)))
                             ((p? (car lst) d) (cons (f1 (car lst) d) (iter (cdr lst) d)))
                             (else (cons (f2 (car lst) d) (iter (cdr lst) d)))))
  ;(if (list? lst) (iter lst 1) (if (p? lst 0) (f1 lst 0) (f2 lst 0))))
 (iter lst 1))


(displayln (deepMapCond '(1 (2 (5 1) 4) 3) > (λ (x d) d) (λ (x d) (* x 2)))) ; -> (2 (4 (3 2) 2) 1)
(displayln (deepMapCond '((1 (3 2) 4) (2 (5 (1 9 2)) 4) 3 (2 3)) > (λ (x d) d) (λ (x d) (* x 2))))