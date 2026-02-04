

cyclic funcs xs ind = for funcs ind
    where
        for [] index = xs !! index
        for (f:fs) index = f (xs !! index) (for fs ((index + 1) `mod` length xs))

findMax fs xs = maximum (map (cyclic fs xs) [0..length xs - 1])

-- >>> findMax [(+),(*),(-)] [2,5]
-- 11

cyclic1 fs xs ind = go ind xs
    where 
        go index [x] = x
        go index (x:xs) = (fs !! index) x (go ((index + 1) `mod` length fs) xs)

findMin fs xs = minimum (map (cyclic1 fs xs) [0..length fs - 1])

-- >>> findMin [(+),(-),(*)] [1,2,0,3,-1]
-- -7

somos k = xs
    where
        xs = replicate k 1 ++ [next n| n <- [k..]]
        next n = (sum [(xs !! (n-i)) * (xs !! (n-k+i)) | i <- [1.. k `div` 2]]) `div` (xs !! (n - k)) 

-- >>> take 10 (somos 4)
-- [1,1,1,1,2,3,7,23,59,314]

prime n = if n < 2 then False else null [x | x <- [2.. n - 1], n `mod` x == 0] 

primeList = [x | x <- [2..], prime x]

madeFromPrime n k
  | k == 1 = prime n
  | otherwise = or [madeFromPrime (n `div` p) (k - 1) | p <- takeWhile (<=n) primeList, n `mod` p == 0]

primitive k = [x | x <- [k..], madeFromPrime x k]

-- >>> take 10 (primitive 3)
-- [8,12,18,20,27,28,30,42,44,45]


insertSort x [] = [x]
insertSort x (y:xs)
  | x < y = x : y : xs
  | otherwise = y : insertSort x xs

sortByX [] =[]
sortByX (x:xs) = insertSort x (sortByX xs)


digits 0 = []
digits n = (n `rem` 10) : digits (n `div` 10)

numbers a b = \k -> sum [x | x <- [a..b], product (digits x) `mod` k == 0]

-- >>> numbers 1 30 3
-- 204


finDecRats = [(p,q) | z <- [2..],
                      p <- [1..z-1],
                      let q = z - p,
                      gcd p q == 1,
                      finiteDecPres q]
            where finiteDecPres q 
                    | q == 1 = True
                    | q `mod` 2 == 0 = finiteDecPres (q `div` 2)
                    | q `mod` 5 == 0 = finiteDecPres (q `div` 5)
                    | otherwise = False

-- >>> take 20 finDecRats
-- [(1,1),(1,2),(2,1),(3,1),(1,4),(3,2),(4,1),(1,5),(5,1),(2,5),(3,4),(5,2),(6,1),(3,5),(7,1),(1,8),(4,5),(5,4),(7,2),(8,1)]



s = [
        (1, "A", 10),
        (1, "B", 5),
        (2, "A", 15),
        (3, "A", 6),
        (3, "A", 10),
        (4, "B", 10),
        (5, "B", 5),
        (6, "B", 6)
        -- (6, "B", 30),
        -- (6, "B", 10),
        -- (7, "B", 20)
    ]

countDays _ [] _ = 0
countDays name ((d,n,_):xs) seen
  | name == n && not (d `elem` seen) = 1 + countDays name xs (d:seen)
  | otherwise = countDays name xs seen


unique [] = []
unique ((_,x,_):xs) = x : filter (/= x) (unique xs)

topShop xs = maxName (unique xs) xs
    where
        maxName [n] _ = n
        maxName (n:ns) ys
          | countDays n ys [] >= countDays (maxName ns ys) ys [] = n
          | otherwise = maxName ns ys

-- >>> topShop s
-- "B"


