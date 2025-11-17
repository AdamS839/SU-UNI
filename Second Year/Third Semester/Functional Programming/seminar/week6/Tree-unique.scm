(define (make-assoc f l)
  (map (lambda (x)
         (cons x (f x))) l))

(define assoc-list (make-assoc (lambda (x) (* x x)) '(1 2 3 4 5)))

(define (unique l)
  (cond ((null? l) `())
        (else (cons (car l) (unique (filter (lambda (x) (not (equal? x (car l)))) (cdr l)))))))

(define (foldr op nv l)
  (if (null? l) nv
      (op (car l) (foldr op nv (cdr l)))))

(define (times x l)
  (foldr (lambda (el res) (+ res (if (= el x) 1 0))) 0 l))

(define (histogram al)
  (unique (map (lambda (x) (cons x (times x al))) al)))

; tree
(define (tree? t)
  (or (null? t)
      (and (list? t)
           (= (length t) 3))
           (tree? (cadr t))
           (tree? (caddr t))))
(define empty-tree '())
(define (make-tree root left right) (list root left right))      
(define (make-leaf root) (make-tree root empty-tree empty-tree))
(define root-tree car)
(define left-tree cadr)
(define right-tree caddr)
(define empty-tree? null?)

(define t (make-tree 5
                     (make-tree 1
                                (make-tree 4
                                           '()
                                           (make-leaf 13))
                                (make-leaf 3))
                     (make-tree 8
                                (make-tree 0
                                           (make-leaf 10)
                                           (make-leaf 9))
                                (make-leaf 11))))



(define (flatten-tree t)
  (if (null? t) `()
      (append (flatten-tree (left-tree t))
              (list (root-tree t))
              (flatten-tree (right-tree t)))))

(define (unique-tree t)
  (unique (flatten-tree t)))

(define (