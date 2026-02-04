
fib 0 = 0
fib 1 = 1
fib n = fib (n - 2) + fib (n - 1)

fastPow _ 0 = 1
fastPow x n 
  | even n = fastPow (x^2) (n `div` 2)
  | otherwise = x * fastPow x (n - 1)

repeat1 _ 0 = id
repeat1 f n = \x -> f (repeat1 f (n - 1) x)


sumSquares a b
  | a > b = 0
  | isSquare a = a + sumSquares (a + 1) b
  | otherwise = sumSquares (a + 1) b
  where isSquare x = let k = floor (sqrt (fromIntegral x)) in k * k == x

  