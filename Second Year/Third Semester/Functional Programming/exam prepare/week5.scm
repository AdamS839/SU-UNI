; problems 5
(define (filter p? l)
  (foldr (lambda (el res) (if (p? el) (cons el res) res)) '() l))

(define (foldr operation null_value lst)
  (if (null? lst) null_value
      (operation (car lst)
          (foldr operation null_value (cdr lst)))))

(define (foldl operation null_value lst)
  (if (null? lst) null_value
      (foldl operation (operation null_value (car lst)) (cdr lst))))

(define (least l)
  (foldr min (car l) (cdr l)))

(define (member? el l)
  (foldr (lambda (x res) (or (equal? x el) res)) #f l))

(define (unique l)
  (foldr (lambda (x res) (if (member? x res) res (cons x res))) `() l))

(define (union l1 l2)
  (unique (append l1 l2)))

(define (intersection l1 l2)
  (filter (lambda (x) (member? x l2)) l1))

;(define (intersection l1 l2)
;  (foldr (lambda (x res) (if (member? x l2) (cons x res) res)) `() (unique l1)))

(define (insert n l)
  (if (null? l) (list n)
      (if (< n (car l)) (cons n l) (cons (car l) (insert n (cdr l))))))

(define (insertion-sort l)
  (foldr (lambda (x res) (insert x res)) `() l))

;(apply + ‘( 1 2 3 4)) ; еквиваленто на (+ 1 2 3 4)

(define (find-interval . xs)
  (- (apply max xs) (apply min xs)))

(define (comp-lex a b)
  (if (string<? a b) a b))

(define (min-lex x . xs)
  (if (null? xs) x
      (comp-lex x (apply min-lex xs))))

(define (succ x) (+ x 1))
(define (^2 x) (* x x))
(define (id x) x)

(define (compose-all2 . fs)
  (if (null? fs) id
      (lambda (x) ((car fs) ((apply compose-all2 (cdr fs)) x)))))

(define dl '((1 2) ((3 (4) 5) (((6)))) (7)))

(define (atom? l)
  (and (not (null? l)) (not (pair? l))))

(define (deep-foldr op term nv l)
  (cond ((null? l) nv)
        ((atom? l) (term l))
        (else (op (deep-foldr op term nv (car l))
                  (deep-foldr op term nv (cdr l))))))

(define (deep-map f dl)
  (deep-foldr (lambda (x res) (cons x res)) (lambda (a) (f a)) `() dl))

(define (deep-filter p? dl)
  (deep-foldr (lambda (x res)
                (if (and (atom? x) (not (p? x))) res (cons x res)))
              (lambda (a) a) `() dl))

(define (deep-member? n dl)
  (deep-foldr (lambda (x y) (or x y)) (lambda (el) (= el n)) #f dl))