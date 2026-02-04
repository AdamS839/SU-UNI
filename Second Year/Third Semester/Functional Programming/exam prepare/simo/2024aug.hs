-- problem 1

windowSum [] _ = 0
windowSum xss k
  | length xss < k = 0
  | otherwise = go (take k xss) (drop k xss) (sum (take k xss))
    where
        go _ [] currMax = currMax
        go window (y:ys) currMax =
            let newWin = tail window ++ [y]
                newSum = sum newWin
                in go newWin ys (max newSum currMax)

-- >>> windowSum [1,2,3,1,3,2,0] 3
-- 7

-- problem 2

unique [] = []
unique (x:xs) = x : filter (/= x) (unique xs)

redundant xss = filter isRedundant allProducts 
    where
        allProducts = unique (concat xss)
        isRedundant num = all (\user -> length (filter (/=num) user) >0) xss

-- >>> redundant [[1,2],[1]]


-- >>> redundant [[1,2],[1,3],[2,3]]
-- [1,2,3]

-- >>> redundant [[1,2],[1,3],[2,3],[3],[4],[5],[3,4,5]]
-- [1,2]

-- problem 4

data BTree = Empty | Node Int BTree BTree
        deriving (Show)

bt = Node 5 (Node 1 (Node 5 (Node 1 Empty Empty)
                            (Node 2 Empty Empty))
                    (Node 2 (Node 3 Empty Empty)
                            (Node 4 Empty Empty)))
            (Node 2 (Node 1 (Node 1 Empty Empty)
                            (Node 7 Empty Empty))
                    (Node 9 (Node 5 Empty Empty)
                            (Node 2 Empty Empty)))

nodeVal Empty = 1
nodeVal (Node v _ _) = v

calcProduct Empty _ = 1
calcProduct (Node v l r) k = 
    let leftVal = nodeVal l
        rightVal = nodeVal r
        prodHere = if leftVal + rightVal > k then v else 1
        in prodHere * calcProduct l k * calcProduct r k

-- >>> calcProduct bt 2
-- 900


