;#lang racket

; problem 1.1

(define phone-book
  '((alice . "555-1234")
    (bob . "555-5678")
    (charlie . "555-9012")))


(define (add-entry key value lst)
  (cons (cons key value) lst))

; problem 1.2

(define (remove-entry key lst)
  (cond ((null? lst) `())
        ((eq? (car (car lst)) key) (cdr lst))
        (else (cons (car lst) (remove-entry key (cdr lst))))))

;problem 1.3

(define (update-entry key value lst)
  (cond ((null? lst) (cons (cons key value) lst))
        ((eq? (car (car lst)) key) (cons (cons key value) (cdr lst)))
        (else (cons (car lst)) (update-entry key value (cdr lst)))))

; problems 2 - Trees

; Дърво (tree) - първият елемент е стойността, останалите са децата

(define simple-tree
  '(1
    (2 (4) (5))
    (3 (6) (7))
    (8)))
; Функции за достъп до елементите на дърво
(define (tree-value tree) (car tree)) ;
(define (tree-children tree) (cdr tree))

; Проверка за листо (възел без деца)
(define (leaf? tree) (null? (tree-children tree)))

; problem 2.1
(define empty-tree? null?) 

(define (atom? t)
  (not (pair? t)))

(define (tree-size t)
  (cond ((null? t) 0)
        ((atom? t) 1)
        (else (+ (tree-size (car t)) (tree-size (cdr t))))))
;(tree-size simple-tree)  ; => 8
;(tree-size '(1))         ; => 1

; problem 2.2

(define (tree-height t)
  (cond ((null? t) 0)
        ((leaf? t) 1)
        (else (+ 1 (apply max (map tree-height (tree-children t)))))))
;(tree-height simple-tree)  ; => 3
;(tree-height '(1))         ; => 1
 

; problem 2.3

(define (tree-leaves t)
  (cond ((null? t) `())
        ((leaf? t) (list (tree-value t)))
        (else (apply append (map tree-leaves (tree-children t))))))
;(tree-leaves simple-tree)  ; => (4 5 6 7 8)

; problem 2.4

(define (tree-sum t)
  (cond ((null? t) 0)
        ((leaf? t) (tree-value t))
        (else (+ (tree-value t) (apply + (map tree-sum (tree-children t)))))))
;(tree-sum simple-tree)  ; => 36 (1+2+3+4+5+6+7+8)


; problem 2.5

(define (tree-map f t)
  (cond ((null? t) `())
        ((leaf? t) (list (f (tree-value t))))
        (else (cons (f (tree-value t)) (map (lambda (child) (tree-map f child)) (tree-children t))))))
;(tree-map (lambda (x) (* x 2)) simple-tree)  ; => (2 (4 (8) (10)) (6 (12) (14)) (16))


; problem 2.6

(define (tree-find p? t)
  (and (not (null? t))
       (or (and (p? (tree-value t)) (tree-value t))
           (and (not (leaf? t))
                (tree-find p? (car (tree-children t)))
                (or (tree-find p? (car (tree-children t)))
                    (and (pair? (cdr (tree-children t)))
                         (tree-find p? (cdr (tree-children t)))))))))

;(define (tree-find p? t)
;  (cond ((null? t) #f)
;        ((p? (tree-value t)) (tree-value t))
;        ((leaf? t) #f)
;        (else (or (tree-find p? (car (tree-children t)))
;         (and (not (null? (cdr (tree-children t))))
;              (tree-find p? (cons (car (cdr (tree-children t)))
;                                  (cdr (cdr (tree-children t))))))))))
