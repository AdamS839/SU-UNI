#lang racket

(define (timesLeft lst)
  (define (iter xs x) (cond ((null? xs) 0)
                            ((equal? (car xs) x) (+ 1 (iter (cdr xs) x)))
                            (else 0)))
  (if (null? lst) 0 (iter lst (car lst))))

(define (encode lst)
  (define (iter l n item count) (cond ((null? l) `())
                                ((not (= 1 n)) (iter (cdr l) (- n 1) item count))
                                ((equal? 1 count) (append (list item) (iter (cdr l) (timesLeft (cdr l)) (if (null? (cdr l)) `() (cadr l)) (timesLeft (cdr l)))))
                                (else (append (list (cons count item)) (iter (cdr l) (timesLeft (cdr l)) (if (null? (cdr l)) `() (cadr l)) (timesLeft (cdr l)))))))
  (iter lst (timesLeft lst) (car lst) (timesLeft lst)))


(define (encode1 lst)
  (define (iter l item count) (cond ((null? l) `())
                                    ((equal? 1 count) (append (list item) (iter (cdr l) (if (null? (cdr l)) `() (cadr l)) (timesLeft (cdr l)))))
                                    (else (append (list (cons count item)) (iter (drop l count) (if (null? (drop l count)) `() (car (drop l count))) (timesLeft (drop l count)))))))
  (iter lst (car lst) (timesLeft lst)))                               

;(displayln (encode '(1 1 1 2 3 3 4))) ; -> ((3 . 1) 2 (2 . 3) 4)
;(displayln (encode (list `a `b `c `a `a `a `f `s `s `s `s `f `f 1 2 2 2))) ; -> (a b c (3 . a) f (4 . s) (2 . f) 1 (3 . 2))

(define (repeat n t) (cond ((zero? t) `())
                           (else (append (list n) (repeat n (- t 1))))))

(define (decode lst) (cond ((null? lst) `())
                           ((pair? (car lst)) (append (repeat (cdar lst) (caar lst)) (decode (cdr lst))))
                           (else (cons (car lst) (decode (cdr lst))))))

; (cons 1 (cons 2 (cons 3 (.... (cons n `()))...) -> `(1 2 3 ... n)

;(displayln (decode `(a b c (3 . a) f (4 . s) (2 . f) 1 (3 . 2))))

(define (addAfterIndex l1 l2 i) (cond ((null? l1) l2)
                                      ((zero? i) (append l2 l1))
                                      (else (append (list (car l1)) (addAfterIndex (cdr l1) l2 (- i 1))))))

;(displayln  (addAfterIndex '(1 2 8 8 8 8 8 8 9) '(8 0 8 8 8) 4)) ; -> '(1 2 8 8 8 0 8 8 8 8 8 8 8 9)

(define (insert l1 l2 i)
  (define (iter lst1 lst2 i) (encode (addAfterIndex lst1 lst2 i)))
  (iter (decode l1) (decode l2) i))

;(displayln (insert '(1 2 (6 . 8) 9) '(8 0 (3 . 8)) 4)) ; -> '(1 2 (3 . 8) 0 (7 . 8) 9)