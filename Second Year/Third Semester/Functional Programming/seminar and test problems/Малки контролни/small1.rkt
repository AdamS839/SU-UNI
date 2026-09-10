#lang racket

; Problem 1

(define (divisor-sum n)
  (define (iter start end sum) (cond ((> start end) sum)
                                     ((zero? (remainder n start)) (iter (+ start 1) end (+ start sum)))
                                     (else (iter (+ start 1) end sum))))
  (iter 1 n 0))

;(displayln (divisor-sum 16)) ; -> 31
;(displayln (divisor-sum 42)) ; -> 96

; Problem 2

(define (square-divisor-sum lst) (cond ((null? lst) `())
                                       ((equal? (ceiling (sqrt (divisor-sum (car lst)))) (sqrt (divisor-sum (car lst)))) (append (list (car lst)) (square-divisor-sum (cdr lst))))
                                       (else (square-divisor-sum (cdr lst)))))

;(displayln (square-divisor-sum '(1 3 42 16)))

(define (make-assoc f l)
 (map (lambda (x)
         (cons x (f x))) l))

(define al '((1 . 2) (5 . 6) (2 . 9) (1 . 13) (18 . 2)))

; Problem 3

(define (get k al nv) (cond ((null? al) nv)
                            ((equal? k (caar al)) (cdar al))
                            (else (get k (cdr al) nv))))

;(displayln (get 2 al 0)) ; -> 9
;(displayln (get 1 al 0) ); -> 2
;(displayln (get 23 al 0)) ; -> 0


; Problem 4

(define (sq x) (* x x))

(define (combine f al) (lambda (x) (if (null? (get x al `())) (f x) (get x al `()))))

;(displayln ((combine sq al) 1)) ; -> 2
;(displayln ((combine sq al) 5)) ; -> 6
;(displayln ((combine sq al) 3)) ; -> 9
