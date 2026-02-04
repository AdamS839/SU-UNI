; problems 6

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

(define (filter p? l)
  (cond ((null? l) l)
        ((p? (car l)) (cons (car l) (filter p? (cdr l))))
        (else (filter p? (cdr l)))))


(define (tree-member? n t)
  (cond ((empty-tree? t) #f)
        (else (or (equal? (root-tree t) n) (tree-member? n (left-tree t)) (tree-member? n (right-tree t))))))

(define (depth t)
  (cond ((empty-tree? t) 0)
        (else (+ 1 (max (depth (left-tree t)) (depth (right-tree t)))))))

; depth with foldr.....

(define (is-leaf t)
  (and (list t) (= (length t) 3) (empty-tree? (left-tree t)) (empty-tree? (right-tree t))))

(define (count-leafs t)
  (cond ((empty-tree? t) 0)
        ((is-leaf t) 1)
        (else (+ (count-leafs (left-tree t)) (count-leafs (right-tree t))))))

(define (traverse t)
  (cond ((empty-tree? t) `())
        (else (append (traverse (left-tree t)) (list (root-tree t)) (traverse (right-tree t))))))

(define (level k t)
  (cond ((empty-tree? t) `())
        ((= k 0) (list (root-tree t)))
        (else (append (level (- k 1) (left-tree t)) (level (- k 1) (right-tree t))))))

; assoc lists

(define (make-assoc f l)
  (map (lambda (x)
         (cons x (f x))) l))

(define assoc-list (make-assoc (lambda (x) (* x x)) '(1 2 3 4 5)))

(define (keys al)
  (cond ((null? al) `())
        (else (append (list (caar al)) (keys (cdr al))))))

(define (values1 al)
  (cond ((null? al) `())
        (else (append (list (cdar al)) (values1 (cdr al))))))

(define (search k al)
  (if (null? al) #f
      (if (= (caar al) k) (car al) (search k (cdr al)))))

;(define (search k al)
;  (assoc k al))


(define (delete k al)
  (cond ((null? al) `())
        ((not (= (caar al) k)) (cons (car al) (delete k (cdr al))))
        (else (delete k (cdr al)))))

(define (delete1 k al)
  (filter (lambda (pair) (not (equal? (car pair) k))) al))

(define (add-assoc k v al)
  (cond ((null? al) (cons k v))
        ((equal? (search k al) #f) (append al (list (cons k v))))
        (else (map (lambda (pair) (if (equal? (car pair) k) (cons k v) pair)) al))))
        
(define (foldl op nv l)
  (if (null? l) nv
      (foldl op (op nv (car l)) (cdr l))))

(define (foldr op nv l)
  (if (null? l) nv
      (op (car l) (foldr op nv (cdr l)))))

;(histogram '(8 7 1 7 8 2 2 8 2 7 8 1)) ; -> '((8 . 4) (7 . 3) (1 . 2) (2 . 3))

(define (unique l)
  (cond ((null? l) `())
        (else (cons (car l) (unique (filter (lambda (x) (not (equal? x (car l)))) (cdr l)))))))

(define (times x l)
  (foldr (lambda (el res) (+ res (if (= x el) 1 0))) 0 l))

(define (histogram l)
  (unique (map (lambda (x) (cons x (times x l))) l)))

; Streams

(define-syntax cons-stream
  (syntax-rules () ((cons-stream h t)
                    (cons h (delay t)))))

(define head car)
(define (tail s) (force (cdr s)))

(define (take n s)
  (cond ((= n 0) `())
        (else (cons (head s) (take (- n 1) (tail s))))))

(define ones (cons-stream 1 ones))
(define (from n) (cons-stream n (from (+ n 1))))

(define nats (from 0))


(define (map-stream f s)
  (cons-stream (f (head s)) (map-stream f (tail s))))

(define (zipstreams op s1 s2)
  (cons-stream (op (head s1) (head s2)) (zipstreams op (tail s1) (tail s2))))

(define fib (cons-stream 0 (cons-stream 1 (zipstreams + fib (tail fib)))))