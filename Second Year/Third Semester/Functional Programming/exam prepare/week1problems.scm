; problems 1

(define (tellnum n)
  (cond ((zero? n) "zero")
        ((> n 0) "positive")
        (else "negative")))

(define (leap-year? y)
  (or (and (zero? (remainder y 4))
           (not (zero? (remainder y 100))))
      (zero? (remainder y 400))))

(define (fact n)
  (cond ((zero? n) 1)
        (else (* n (fact (- n 1))))))

(define (fib n)
  (cond ((zero? n) 0)
        ((= n 1) 1)
        (else (+ (fib (- n 1)) (fib (- n 2))))))

(define (fib1 n)
  (define (helper i fi fi-1)
    (cond ((= i n) fi-1)
          (else (helper (+ i 1) (+ fi fi-1) fi))))
  (helper 0 1 0))


(define (interval-sum a b)
  (cond ((= a b) a)
        (else (+ a (interval-sum (+ a 1) b)))))

(define (interval-sum2 a b)
  (cond ((or (= a b) (= (+ a 1) b)) 0)
        (else (+ (+ a 1) (interval-sum2 (+ a 1) b)))))

(define (count-digit d n)
  (cond ((and (zero? n) (zero? d)) 0)
        ((and (zero? n) (not (zero? d))) 0)
        ((= d n) 1)
        ((= d (remainder n 10)) (+ 1 (count-digit d (quotient n 10))))
        (else (+ 0 (count-digit d (quotient n 10))))))

(define (count-digit-interval d a b)
  (cond ((= a b) (count-digit d a))
        (else (+ (count-digit d a) (count-digit-interval d (+ a 1) b)))))

(define (number-length n)
  (cond ((zero? n) 1)
        ((zero? (quotient n 10)) 1)
        (else (+ 1 (number-length (quotient n 10))))))

(define (reverse-digits n)
  (cond ((zero? n) 0)
        (else (+ (* (remainder n 10) (expt 10 (- (number-length n) 1))) (reverse-digits (quotient n 10))))))
