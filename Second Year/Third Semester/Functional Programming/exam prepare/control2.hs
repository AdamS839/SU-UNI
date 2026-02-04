
-- problem 1

-- denominators = [2^a * 5^b | s <- [0..],
--                             a <- [0..s],
--                             let b = s - a]

-- finDecRats = [(p,q)| z <- [1..],
--                      p <- [1..z],
--                      q <- take z denominators,
--                      gcd p q == 1]


finDecRats =
  [ (p, q)
  | s <- [0..]
  , p <- [1..s+1]
  , a <- [0..s]
  , let b = s - a
  , let q = 2^a * 5^b
  , gcd p q == 1
  ]


-- problem 3

s = [
        (1, "A", 10),
        (1, "B", 5),
        (2, "A", 15),
        (3, "A", 6),
        (3, "A", 10),
        (4, "B", 10),
        (5, "B", 5),
        (6, "B", 6),
        (6, "B", 30),
        (6, "B", 10),
        (7, "B", 20)
    ]

getFirst (a,b,c) = a
getSecond (a,b,c) = b
getThird (a,b,c) = c

maxDay [a] = getFirst a
maxDay ((d1,n1,p1):(d2,n2,p2):xs) 
  | p1 >= p2 = maxDay ((d1,n1,p1):xs)
  | otherwise = maxDay ((d2,n2,p2):xs)

-- Count how many unique days a name appears
countDays _ [] _ = 0
countDays name ((d,n,_):xs) seen
  | n == name && not (d `elem` seen) = 1 + countDays name xs (d:seen)
  | otherwise = countDays name xs seen

getStreakDays _ [] _ = []
getStreakDays name ((d,n,p):xs) seen
 | n == name && not (d `elem` seen) && p > 0 = d : getStreakDays name xs (d:seen)
 | otherwise = getStreakDays name xs seen

-- >>> getStreakDays "A" s []
-- [1,2,3]

mustNextDay [] = []
mustNextDay [a] = [a]
mustNextDay (x:y:xs)
  | y == x + 1 = x : y : mustNextDay xs
  | otherwise = y : mustNextDay xs

-- Get list of all names (no duplicates)
names [] = []
names ((_,n,_):xs) = n : filter (/= n) (names xs)

-- Find name with max days
topShop xs = maxName (names xs) xs
  where
    maxName [n] _ = n
    maxName (n:ns) ys
      | countDays n ys [] >= countDays (maxName ns ys) ys [] = n
      | otherwise = maxName ns ys

-- >>> topShop s
-- "B"

uniqueNames [] = []
uniqueNames ((_,n,_):xs) = n : filter (/= n) (uniqueNames xs)

allStreaks xs = [(n, length $ mustNextDay $ getStreakDays n xs []) | n <- uniqueNames xs]

streakP [a] = snd a
streakP ((n1,c1):(n2,c2):xs) 
  | c1 >= c2 = streakP ((n1,c1):xs)
  | otherwise = streakP ((n2,c2):xs)

streak xs = streakP $ allStreaks xs
