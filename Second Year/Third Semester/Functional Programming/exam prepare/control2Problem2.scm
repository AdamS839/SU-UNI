(define (lambda-form? x)
  (and (list? x)
       (= (length x) 3) (eq? (car x) `lambda)))

(define (andmap pred lst)
  (if (null? lst)
      #t
      (and (pred (car lst)) (andmap pred (cdr lst)))))

(define (looksLikeComb x)
  (cond ((null? x) #t)
        ((not (list? x)) #t)
        (else (and (let ((f (car x)))
                     (or (procedure? f)
                         (lambda-form? f)
                         (symbol? f)))
                   (andmap looksLikeComb x)))))