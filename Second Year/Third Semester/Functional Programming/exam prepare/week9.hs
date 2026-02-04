

evenCubes [] = []
evenCubes (x:xs)
  | even x = x^3 : evenCubes xs
  | otherwise = evenCubes xs

pair x l = map (\y -> (x, y)) l

descartes [] [] = []
descartes _ [] = []
descartes [] _ = []
-- descartes (x:xs) l = pair x l ++ descartes xs l

descartes xs ys = [(x,y) | x <- xs, y <- ys, (x + y) `mod` 3 == 0 ]

histogram [] = []
histogram (x:xs) = (x, 1 + count x xs) : histogram xs
                   where count x = length . filter (== x)

mostCommonWordP [x] = x
mostCommonWordP (x:y:args)
  | snd x >= snd y = mostCommonWordP (x:args)
  | otherwise = mostCommonWordP (y:args)

mostCommonWord text = fst (mostCommonWordP (histogram (words text)))

-- infinite lists

repeat' a = a : repeat' a

fib = 0 : 1 : fibT
      where fibT = zipWith (+) fib (tail fib)

factList = 1 : zipWith (*) factList [1..]

-- no problem 8
