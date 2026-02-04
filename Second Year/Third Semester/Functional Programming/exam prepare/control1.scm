; control 1

;pr 1

(define (getsum n)
  (cond ((< n 10) n)
        (else (+ (remainder n 10) (getsum (quotient n 10))))))

(define (minDiv num)
  (define (helper b n)
    (cond ((zero? (remainder n b)) b)
          (else (helper (+ b 1) n))))
  (if (< (getsum num) 2) 1с
      (helper 2 (getsum num))))

; pr 2


(define (foldr op nv l)
  (if (null? l) nv
      (op (car l) (foldr op nv (cdr l)))))

(define (longer a b)
  (if (> (length a) (length b)) a b))

(define (maxSub f l)
  (define (helper lst curr best)
    (cond ((null? lst) (longer curr best))
          ((> (f (car lst)) 0) (helper (cdr lst) (append curr (list (car lst))) best))
          (else (helper (cdr lst) `() (longer curr best)))))
  (helper l `() `()))

(define (maxSub1 f l)
  (foldr longer `() (foldr (lambda (x res) (if (> (f x) 0) (cons (cons x (car res)) (cdr res)) (cons `() res))) (list `()) l)))

; pr 3

(define (tree? t)
  (or (null? t)
      (and (list? t)
           (= (length t) 3))
           (tree? (cadr t))
           (tree? (caddr t))))

(define t
  '(a
     (b (c () ()) (b () ()))
     (b (b () ()) (a () ()))))

(define (collectKeys t)
  (define (helper t acc)
    (cond ((null? t) acc)
          (else (let ((v (car t))
                      (l (cadr t))
                      (r (caddr t)))
                  (helper r (helper l (if (member v acc) acc (cons v acc))))))))
  (helper t `()))
                

(define (find-rightmost-subtree key tree)
  (cond
    ((null? tree) '())
    (else
     (let* ((curr-val (car tree))
            (left-sub (cadr tree))
            (right-sub (caddr tree))
            (from-right (find-rightmost-subtree key right-sub)))
       (cond
         ((not (null? from-right)) from-right)
         ((eq? curr-val key) tree)
         (else (find-rightmost-subtree key left-sub)))))))

(define (buildAssoc t)
  (define keys (reverse (collectKeys t)))
  (define (process-key key)
    (cons key (find-rightmost-subtree key t)))
  (map process-key keys))