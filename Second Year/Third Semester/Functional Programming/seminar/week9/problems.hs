-- problem 1

longestPrefix p xs = helper p xs [] []
    where helper p [] prefix maxPrefix = maxPrefix
          helper p (y : ys) prefix maxPrefix = let newPrefix = prefix ++ [y]
            in if p newPrefix then helper p ys newPrefix newPrefix else helper p ys newPrefix maxPrefix

longestSublist :: ([a] -> Bool) -> [a] -> [a]
longestSublist p [] = []
longestSublist p (x:xs) = let lhs = longestPrefix p (x:xs)
                              rhs = longestSublist p xs 
            in if length lhs >= length rhs then lhs else rhs 

-- problem 2 - evenCubes
evenCubes [] = []
evenCubes (x:xs) = map (\ x -> x^3) (filter even (x:xs))

-- problem 3
pair x list = map (\y -> (x, y)) list

descartes :: Integral b => [b] -> [b] -> [(b, b)]
descartes [] [] = []
descartes _ [] = []
descartes [] _ = []
--descartes (x:xs) list = pair x list ++ descartes xs list

descartes xs ys = [(x,y) | x <- xs,
                           y <- ys,
                           (x + y) `mod` 3 == 0]

-- problem 4

-- problem 5
repeat' a = a : repeat' a 

-- problem 6
fib :: [Integer]
fib = 0 : 1 : zipWith (+) (tail fib) fib
--fib = fibh 0 1
--    where fibh a b = a : fibh b (a + b)

-- problem 7
nats :: [Integer]
nats = [0..]

factList :: [Integer]
factList = map fact nats
         where fact 0 = 1
               fact n = n * fact (n - 1)

-- problem 8
--subsetList [] = [[]]
--let rest = subsets xs
--head rest ++ map (x:) ++ tail rest
