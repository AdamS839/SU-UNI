#lang racket

; problem 1

; a)
(define (sumDels n)
  (define (iter start end sum) (cond ((> start end) sum)
                                     ((zero? (remainder n start)) (iter (+ start 1) end (+ sum start)))
                                     (else (iter (+ start 1) end sum))))
  (iter 1 (- n 1) 0))

(define (done? n) (if (equal? 2 (- (sumDels n) n)) #t #f))

; b)

(define (find-done a b) (cond ((> a b) `())
                              ((done? a) (cons a (find-done (+ a 1) b)))
                              (else (find-done (+ a 1) b))))

(define (getBetterPoint start end doned x) (if (or (<= (abs (- x start)) (abs (- doned x))) (<= (abs (- end x)) (abs (- doned x)))) 0 x))

(define (sum-almost-done start end)
  (define (getSums doneLst s sum sumLst) (cond ((null? doneLst) (cons sum sumLst))
                                           ((> s end) (getSums (cdr doneLst) start 0 (cons sum sumLst)))
                                           (else (getSums doneLst (+ s 1) (+ sum (getBetterPoint start end (car doneLst) s)) sumLst))))
  (foldl max 0 (getSums (find-done start end) start 0 `())))


; problem 2

(define (id x) x)


(define (apply-proc op limit lst) (cond ((or (symbol? (car lst)) (symbol? (cadr lst)) (null? lst)) lst)
                                        ((zero? limit) (cons (op (car lst) (cadr lst)) (cddr lst)))
                                        (else (apply-proc op (- limit 1) (cons (op (car lst) (cadr lst)) (cddr lst))  ))))

(define (run-machine lst)
  (define (iter ins stack) (cond ((null? ins) stack)
                                 ((or (symbol? (car ins)) (number? (car ins))) (iter (cdr ins) (cons (car ins) stack)))
                                 ((procedure? (car ins)) (iter (cdr ins) (map (lambda (x) (if (number? x) ((car ins) x) (id x))) stack)))
                                 ((and (pair? (car ins))
                                       (procedure? (caar ins))
                                       (number? (cdar ins))
                                       (number? (car stack))
                                       (number? (cadr stack)) (number? (car stack)) (number? (cadr stack)))
                                               (iter (cdr ins) (apply-proc (caar ins) (- (cdar ins) 1) stack)))))
                                 
  (iter lst `()))


;(displayln (run-machine (list 1 'x 4 'a 9 16 25 sqrt 6))) ;                       -> (6 5 4 3 a 2 x 1)
;(displayln (run-machine (list 1 'x 4 'a 9 16 25 sqrt 6 (cons + 2) (cons * 5)))) ; -> (45 a 2 x 1)


; problem 3

(define (sub-major? l1 l2)
  (define (iter lst1 lst2 start) (cond ((null? lst1) #t)
                                       ((null? lst2) #f)
                                       ((<= (car lst1) (car lst2)) (iter (cdr lst1) (cdr lst2) start))
                                       (else (iter l1 (cdr start) (cdr start)))))
  (iter l1 l2 l2))

                               
(define (is-major? lst) (cond ((null? lst) #t)
                              ((equal? 1 (length lst)) #t)
                              (else (and (sub-major? (car lst) (cadr lst)) (is-major? (cdr lst))))))


;(displayln (sub-major? `(1 3) `(4 2 7))); -> #t
;(displayln (sub-major? `(4 2 7) `(2 5 4 3 9 12))) ;-> #t
;(displayln (is-major? '((1 3) (4 2 7) (2 5 4 3 9 12)))) ; -> #t

;(displayln (is-major? '((1 3) (4 2 7) (2 5 3 3 9 12)))) ; -> #f