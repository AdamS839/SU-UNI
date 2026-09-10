#lang racket


; problem 1

(define (digitSum n) (cond ((zero? n) 0)
                           (else (+ (remainder n 10) (digitSum (quotient n 10))))))

(define (minDiv n)
  (define (iter num start end) (cond ((> start end) 1)
                                     ((zero? (remainder num start)) start)
                                     (else (iter num (+ start 1) end))))
  (iter (digitSum n) 2 (ceiling (sqrt (digitSum n)))))

;(displayln (minDiv 24)) ;-> 2
;(displayln (minDiv 1000)) ;-> 1

; problem 2

(define (maxLen l1 l2) (if (<= (length l1) (length l2)) l2 l1))

(define (maxSub f l)
  (define (iter f curr best l) (cond ((null? l) best)
                                      ((> (f (car l)) 0) (iter f (append curr (list (car l))) best (cdr l)))
                                      (else (iter f `() (maxLen curr best) (cdr l)))))
  (iter f `() `() l))

(define (maxSubF f l)
  (cadr (foldl
   (lambda (x state)
     (let ((curr (car state))
           (best (cadr state)))
       (if (> (f x) 0)
           (let ((new-curr (append curr (list x))))  ;if true
             (list new-curr
                   (if (> (length new-curr)
                          (length best))
                       new-curr
                       best)))
           (list '()                                 ;if false
                 (if (> (length curr)
                        (length best))
                     curr
                     best)))))
   (list '() '())
   l)))
          

;(display (maxSub (lambda (x) (- (abs x) 1)) `(-3 -2 -1 0 1 2 3 4 -1 -3))) ;-> (2 3 4)
;(display (maxSubF (lambda (x) (- (abs x) 1)) `(-3 -2 -1 0 1 2 6 7 8 9 3 4 -1 -3))) ;-> (2 6 7 8 9 3 4)


; problem 3

(define t `("a" ("b" ("c" () ()) ()) ("b" ("b" () ()) ("a" () ()))))


(define (unique lst) (cond ((null? lst) `())
                           (else (cons (car lst) (unique (filter (lambda (x) (not (equal? (car lst) x))) (cdr lst)))))))


(define (getElems t) (cond ((null? t) `())
                           (else (append (list (car t)) (getElems (cadr t)) (getElems (caddr t))))))


(define (getUniqueElems t) (unique (getElems t)))


(define (getTreeElem key t)
  (define (iter valid tree key) (cond ((null? tree) valid)
                                      ((equal? (car tree) key) (iter tree (caddr tree) key))
                                      (else (define right-result (iter valid (caddr tree) key))
                                            (if (null? right-result) (iter valid (cadr tree) key) right-result))))
  (iter `() t key))
  

(define (buildAssoc t)
  (define (iter lst t) (cond ((null? lst) `())
                             (else (cons (cons (car lst) (list (getTreeElem (car lst) t))) (iter (cdr lst) t)))))
  (iter (getUniqueElems t) t))

(displayln (buildAssoc t)) ;-> (("a" ("a" () ())) ("b" ("b" ("b" () ()) ("a" () ()))) ("c" ("c" () ())))








