; problems 3

(define (id x) x)

(define (5+ x) (+ x 5))

(define (3* x) (* x 3))

(define (compose f g)
  (lambda (x) (f (g x))))

(define (flip f) (lambda (x y) (f y x)))

(define (repeat f n)
  (if (= n 0) id
      (compose f (repeat f (- n 1)))))

(define (twist k f g)
  (if (= k 0) id
      (compose (if (even? k) f g) (twist (- k 1) f g))))

;examples
(define (++ x) (+ x 1))
(define (sq x) (* x x))
(define foo (twist 4 ++ sq))
; това ще смята ((((x^2)+1)^2)+1)
(define bar (twist 2 ++ sq))
; това ще смята ((x^2)+1)

(define (curry f) (lambda (x) (lambda (y) (f x y))))

(define (accumulate operation null-value begin end term next)
  (if (> begin end) null-value
      (operation (term begin)
                 (accumulate operation null-value (next begin) end term next))))

(define (!! num)
  (accumulate * 1 (if (even? num) 2 1) num id (lambda (x) (+ x 2))))

(define (sum-odd-squares a b)
  (accumulate + 0 (if (even? a) (+ a 1) a) b (lambda (x) (* x x)) (lambda (x) (+ x 2))))

(define (binomial n k)
  (accumulate * 1 1 k (lambda (x) (/ (- (+ 1 n) x) x)) (lambda (x) (+ x 1))))

(define (argmax f a b)
  (accumulate (lambda (x y) (if (< (f x) (f y)) y x)) a a b id (lambda (x) (+ x 1))))

(define (all? p? a b)
  (accumulate (lambda (x y) (and x y)) #t a b p? (lambda (x) (+ x 1))))

(define (any? p? a b)
  (accumulate (lambda (x y) (or x y)) #f a b p? (lambda (x) (+ x 1))))

(define (digits-count n)
  (if (zero? n) 1
  (accumulate + 0 1 n (lambda (x) 1) (lambda (x) (* x 10)))))

(define (prime? n)
  (if (< n 2) #f
      (all? (lambda (x) (not (zero? (remainder n x)))) 2 (/ n 2))))

(define (prime2? n)
  (if (< n 2) #f
      (accumulate (lambda (x y) (and x y)) #t 2 (floor (sqrt n)) (lambda (x) (not (zero? (remainder n x)))) (lambda (x) (+ x 1)))))

(define (repeat1 f n)
  (accumulate compose id 1 n (lambda (x) f) (lambda (x) (+ x 1))))

(define (twist1 n f g)
  (accumulate compose id 1 n (lambda (x) (if (even? x) f g)) (lambda (x) (+ x 1))))