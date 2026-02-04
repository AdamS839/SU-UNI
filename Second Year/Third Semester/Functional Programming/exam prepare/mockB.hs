

prime n = if n > 1 then null [x | x <- [2..n-1], n `mod` x == 0] else False

primeList = [x | x <- [2..], prime x]

madeFromPrime size num
  | size == 1 = prime num
  | otherwise = or [madeFromPrime (size - 1) (num `div` p) | p <- takeWhile (<=num) primeList, num `mod` p == 0]

primitive k = [x | x <- [k..], madeFromPrime k x]


-- >>> take 10 (primitive 3)
-- [8,12,18,20,27,28,30,42,44,45]
