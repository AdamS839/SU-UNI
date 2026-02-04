; problems 4

(define (length1 l)
  (cond ((null? l) 0)
        (else (+ 1 (cdr l)))))

(define (reverse1 l)
  (cond ((null? l) `())
        (else (append (reverse1 (cdr l)) (list (car l))))))

(define (map1 f l)
  (cond ((null? l) `())
        (else (append (list (f (car l))) (map1 f (cdr l))))))

(define (filter p? l)
  (cond ((null? l) l)
        ((p? (car l)) (append (list (car l)) (filter p? (cdr l))))
        (else (filter p? (cdr l)))))

(define (at n l)
  (define (helper i count lst)
    (cond ((null? lst) `())
          ((= i count) (car lst))
          (else (helper (+ i 1) count (cdr lst)))))
  (helper 0 n l))

(define (take n l)
    (cond ((null? l) `())
          ((not (zero? n)) (append (list (car l)) (take (- n 1) (cdr l))))
          (else `())))

(define (drop n l)
  (cond ((null? l) `())
        ((not (zero? n)) (drop (- n 1) (cdr l)))
        (else l)))

(define (append1 l1 l2)
  (cond ((null? l1) l2)
        ((null? l2) l1)
        (else (cons (car l1) (append1 (cdr l1) l2)))))

(define (all? p? l)
  (equal? l (filter p? l)))

(define (any? p? l)
  (not (null? (filter p? l))))

(define (zipWith f l1 l2)
  (cond ((null? l1) l2)
        ((null? l2) l1)
        (else (append (list (f (car l1) (car l2))) (zipWith f (cdr l1) (cdr l2))))))

(define (zip l1 l2)
  (zipWith cons l1 l2))

(define (sorted? l)
  (cond ((or (null? l) (= 1 (length l))) #t)
        ((< (car l) (cadr l)) (sorted? (cdr l)))
        (else #f)))

(define (foldr operation null_value lst)
  (if (null? lst) null_value
      (operation (car lst)
          (foldr operation null_value (cdr lst)))))

(define (foldl operation null_value lst)
  (if (null? lst) null_value
      (foldl operation (operation null_value (car lst)) (cdr lst))))

(define (length2 l)
  (foldr (lambda (el res) (+ res 1)) 0 l))

(define (length3 l)
  (foldl (lambda (res el) (+ res 1)) 0 l))

(define (all?1 p? l)
  (foldr (lambda (x res) (and (p? x) res)) #t l))

(define (all?2 p? l)
  (foldr (lambda (res x) (and (p? res) x)) #t l))

(define (any?1 p? l)
  (foldr (lambda (x res) (or (p? x) res)) #f l))

(define (any?2 p? l)
  (foldl (lambda (res x) (or (p? x) res)) #f l))

(define (reverse2 l)
  (foldr (lambda (x res) (append res (list x))) `() l))

(define (reverse3 l)
  (foldl (lambda (res x) (append (list x) res)) `() l))

(define (map2 f l)
  (foldr (lambda (x res) (append (list (f x)) res)) `() l))

(define (map3 f l)
  (foldl (lambda (res x) (append res (list (f x)))) `() l))

(define (filter2 p? l)
  (foldr (lambda (x res) (if (p? x) (append (list x) res) res)) `() l))

(define (filter3 p? l)
  (foldl (lambda (res x) (if (p? x) (append res (list x)) res)) `() l))