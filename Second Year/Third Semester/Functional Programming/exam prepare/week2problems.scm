; problems 2

(define (fact n)
  (cond ((zero? n) 1)
        (else (* n (fact (- n 1))))))

(define (fib n)
  (define (helper i fi fi-1)
    (cond ((= i n) fi-1)
          (else (helper (+ i 1) (+ fi fi-1) fi))))
  (helper 0 1 0))

(define (interval-sum a b)
  (cond ((= a b) a)
        (else (+ a (interval-sum (+ a 1) b)))))

(define (pow-i x n)
  (define (helper i res counter mult)
    (cond ((zero? x) 0)
          ((zero? n) 1)
          ((= i counter) res)
          (else (helper (+ i 1) (* res mult) counter mult))))
  (helper 0 1 n x))

(define (to-binary n)
  (cond ((< n 2) n)
        (else (+ (remainder n 2) (* 10 (to-binary (quotient n 2)))))))

(define (to-decimal n)
  (cond ((< n 10) n)
        (else (+ (remainder n 10) (* 2 (to-decimal (quotient n 10)))))))

(define (prime? n)
  (define (helper i num)
    (cond ((= i num) #t)
          ((zero? (remainder num i)) #f)
          (else (helper (+ i 1) num))))
  (if (< n 2) #f)
  (helper 2 n))