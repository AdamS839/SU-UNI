
{-
fib :: (Eq t1, Num t1, Num t2) => t1 -> t2
fib 0 = 0
fib 1 = 1
fib n = fib (n-1) + fib (n-2)
-}

fib n
  | n == 0 = 0
  | n == 1 = 1
  | otherwise = fib (n-1) + fib (n-2)

fibIF n = if n == 0 then 0 else if n == 1 then 1 else fibIF (n-1) + fibIF (n-2)

fib1 n = fibiter 0 1 n
  where fibiter a b 0 = a
        fibiter a b n = fibiter b (a+b) (n - 1)

fastPow a n 
    | n == 0 = 1
    | even n && n > 0 = (fastPow a (n `div` 2))^2
    | otherwise = (fastPow a ((n-1) `div` 2))^2 * a

repeat1 :: (Eq t, Num t) => (b -> b) -> t -> b -> b
repeat1 f n
    | n == 0 = id
    | otherwise = f . repeat1 f (n - 1)

sumSquares a b 
    | a > b = 0
    | (floor (sqrt (fromIntegral a)))^2 == a = a + sumSquares (a + 1) b
    | otherwise = sumSquares (a + 1) b