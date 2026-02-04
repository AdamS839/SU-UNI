-- problem 2

-- >>> 

-- problem 3

digits 0 = []
digits q = q `rem` 10 : digits (q `div` 10)

-- >>> digits 123
-- [3,2,1]

numbers a b = \k -> sum [q | q <- [a..b], product (digits q) `mod` k == 0]

-- >>> numbers 1 40 7
-- 188

-- >>> numbers 1 5 7
-- 0

-- problem 4

data BTree = Empty | Node Int BTree BTree 
        deriving (Show)

t1 = Node 6 (Node 3 (Node 2 Empty Empty)
                    (Node 5 (Node 4 Empty Empty)
                            Empty))
            (Node 8 (Node 7 Empty Empty)
                    (Node 9 Empty Empty))


solveList [] = 0
solveList [x] = x
solveList (x:xs) = x * (10 ^ (length (x:xs) - 1)) + solveList xs

generateList Empty _ = []
generateList bt k = go bt k False
     where
        go Empty _ _ = []
        go (Node v l r) level isLeft
           | level == 0 && isLeft = [v]
           | level == 0 = []
           | otherwise = go l (level-1) True ++ go r (level-1) False

generateNum bt k = solveList $ generateList bt k

-- >>> generateNum t1 2
-- 27

-- >>> generateNum t1 3
-- 4


