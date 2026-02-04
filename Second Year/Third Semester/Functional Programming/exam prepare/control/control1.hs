

getSum 0 = 0
getSum num = num `rem` 10 + getSum (num `div` 10)

-- >>> getSum 24
-- 6

-- >>> getSum 1000
-- 1

minDiv n = if (getSum n) < 2 then 1 else minimum [ x | x <- [2..(getSum n)], (getSum n) `mod` x == 0]

-- >>> minDiv 54
-- 3

-- >>> minDiv 1000
-- 1

maxSub f xs = getBest xs [] []
    where
        getBest [] curr best
          | length curr > length best = curr
          | otherwise = best
        getBest (x:xs) curr best
          | f x > 0 = getBest xs (curr ++ [x]) (if length (curr++[x]) > length best then curr++[x] else best) 
          | otherwise = getBest xs [] best


-- >>> maxSub (\x -> abs x - 1) [-3, -2, -1, 0, 1, 2, 3, 4, -1, -3]
-- [2,3,4]


data BinTree a = Empty | Node a (BinTree a) (BinTree a)
    deriving (Show, Eq, Ord)

t = Node 'a' (Node 'b' (Node 'c' Empty Empty) Empty) (Node 'b' (Node 'd' Empty Empty) (Node 'a' Empty Empty))

getVal Empty = []
getVal (Node a Empty Empty) = [a]
getVal (Node a left right) = [a] ++ getVal left  ++ getVal right 

-- >>> getVal t
-- "abcbba"

getUnique [] = []
getUnique (x:xs) = x : filter (/= x) (getUnique xs)

-- >>> getUnique $ getVal t
-- "abc"

findRightSub Empty _ = Empty
findRightSub (Node v l r) k
    | rightRes /= Empty = rightRes
    | v == k = Node v l r
    | otherwise = leftRes
      where
        rightRes = findRightSub r k
        leftRes = findRightSub l k
    
-- >>> findRightSub t 'a'
-- Node 'a' Empty Empty

-- >>> findRightSub t 'b'
-- Node 'b' (Node 'd' Empty Empty) (Node 'a' Empty Empty)

-- >>> findRightSub t 'c'
-- Node 'c' Empty Empty

-- >>> findRightSub t 'd'
-- Node 'd' Empty Empty

buildAssoc t = zip (getUnique $ getVal t) (map (findRightSub t) (getUnique $ getVal t))

-- >>> buildAssoc t
-- [('a',Node 'a' Empty Empty),('b',Node 'b' (Node 'd' Empty Empty) (Node 'a' Empty Empty)),('c',Node 'c' Empty Empty),('d',Node 'd' Empty Empty)]
