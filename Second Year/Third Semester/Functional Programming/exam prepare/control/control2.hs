

type Day = Integer
type Name = String
type Price = Integer

type List = [(Day, Name, Price)]

s = [
    (1,"A",10),
    (1,"B",5),
    (2,"A",15),
    (3,"A",6),
    (3,"A",10),
    (4,"B",10),
    (5,"B",5),
    (6,"B",6)
    ]

getFirst (a,_,_) = a

maxDay [x] = getFirst x
maxDay ((d1,n1,p1):(d2,n2,p2):xs)
  | p1 >= p2 = maxDay ((d1,n1,p1):xs)
  | otherwise = maxDay ((d2,n2,p2):xs)

-- >>> maxDay s
-- 2

names [] = []
names ((_,n,_):xs) = n : filter (/= n) (names xs)

-- >>> names s
-- ["A","B"]

getDaysCount _ [] _ = 0
getDaysCount name ((d,n,_):xs) seen 
  | name == n && not (d `elem` seen) = 1 + getDaysCount name xs (d:seen)
  | otherwise = getDaysCount name xs seen

-- >>> getDaysCount "A" s []
-- 3

-- >>> getDaysCount "B" s []
-- 4

topShop xs = maxName (names xs) xs
    where
        maxName [n] _ = n
        maxName (n:ns) ys
           | getDaysCount n ys [] >= getDaysCount (maxName ns ys) ys [] = n
           | otherwise = maxName ns ys

-- >>> topShop s
-- "B"

getStreakDays _ [] _ = []
getStreakDays name ((d,n,p):xs) seen
  | name == n && not (d `elem` seen) && p > 0 = d : getStreakDays name xs (d:seen)
  | otherwise = getStreakDays name xs seen 

-- >>> getStreakDays "A" s []
-- [1,2,3]

-- >>> getStreakDays "B" s []
-- [1,4,5,6]

mustBeNextDay [] = []
mustBeNextDay [x] = [x]
mustBeNextDay (d1:d2:ds)
  | d1 == d2 - 1 = d1 : mustBeNextDay (d2:ds)
  | otherwise = mustBeNextDay (d2:ds)

-- >>> mustBeNextDay (getStreakDays "B" s [])
-- [4,5,6]

allStreaks xs = [(n, length $ mustBeNextDay $ getStreakDays n xs []) | n <- (names xs)]

-- >>> allStreaks s
-- [("A",3),("B",3)]

getSecond (_,a) = a

getBestStreak [x] = getSecond x
getBestStreak ((n1,s1):(n2,s2):xs)
  | s1 >= s2 = getBestStreak ((n1,s1):xs)
  | otherwise = getBestStreak ((n2,s2):xs)

streak xs = getBestStreak $ allStreaks xs

-- >>> streak s
-- 3

