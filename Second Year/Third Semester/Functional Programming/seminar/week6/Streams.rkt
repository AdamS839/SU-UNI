; Streams

(define-syntax cons-stream
  (syntax-rules () ((cons-stream h t)
                    (cons h (delay t)))))

(define head car)
(define (tail s) (force (cdr s)))

(define s (cons-stream 1 (cons-stream 2 (cons-stream 3 (cons-stream 4 (cons-stream 5 (cons-stream 6 (the-empty-stream))))))))

; problem 1 - get n index

(define (take n s)
  (if (or (null? s) (= n 0)) `()
      (cons (head s) (take (- n 1) (tail s)))))

; problem 2 - nats

(define (stream-from n)
  (cons-stream n (stream-from (+ n 1))))

(define nats (stream-from 0))

; problem 3 - map-stream

(define (map-stream f s)
  (cons-stream (f (head s)) (map-stream f (tail s))))

; problem 4 - fib
(define (add-stream s1 s2)
   (cons-stream (+ (head s1) (head s2)) (add-stream (tail s1) (tail s2))))

(define fib (cons-stream 0 (cons-stream 1 (add-stream fib (tail fib)))))

