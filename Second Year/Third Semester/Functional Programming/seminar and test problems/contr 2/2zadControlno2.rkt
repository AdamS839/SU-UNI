#lang racket

(define (hasProc? l) (cond ((procedure? (car l)) #t)
                             (else #f)))

(define (hasLambdaList? l) (cond ((and (list? (car l)) (equal? 3 (length (car l))) (equal? `lambda (caar l))) #t)
                                 (else #f)))

(define (looksLikeComb l)
  (define (iter lst currPos) (cond ((null? lst) #t)
                                   ((hasProc? lst) (iter (cdr lst) (+ currPos 1)))
                                   ((hasLambdaList? lst) (and (iter (list (cadr lst)) 1) (iter (cdr lst) (+ currPos 1))))
                                   ((list? (car lst)) (and (iter (car lst) 0) (iter (cdr lst) currPos)))
                                   ((> currPos 0) (iter (cdr lst) (+ currPos 1)))
                                   (else #f)))
  (iter l 0))

(displayln (looksLikeComb (list + 4 (list 3 4))))
(displayln (looksLikeComb (list (list `lambda `(x) `x) 4 (list (list `lapa `(x) `x) 3 4))))
(displayln (looksLikeComb (list - 5 (list (list 'lambda '(x) 'x) 10))))