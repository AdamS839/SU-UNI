
fact :: Integer -> Integer
fact 0 = 1
fact n = n * fact (n - 1)

-- problem 1

fib :: Integer -> Integer
fib 0 = 0
fib 1 = 1
fib 2 = 1
fib n = fib (n - 1) + fib (n - 2)

-- problem 2

--fastPow :: (Integer -> Integer) -> Integer
fastPow x n 
    | x == 1    = x
    | n == 0    = 1
    | even n    = x * (x ^ 2) ^ ((n - 1)/2)
    | odd n     = (x ^ 2)^(n/2)