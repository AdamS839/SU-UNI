data BinTree a = Nil | Node a (BinTree a) (BinTree a)
    deriving (Show, Eq, Ord)

charBTree = Node 'k' (Node 'a' (Node 'h' Nil Nil) (Node 's' Nil Nil)) (Node 'l' (Node 'e' Nil Nil) (Node 'l' Nil Nil))

numberBTree = Node 5 (Node 12 (Node 1 (Node 96 Nil Nil) Nil) (Node 0 Nil Nil)) (Node 4 (Node 2 Nil Nil) (Node 5 Nil (Node 21 Nil Nil)))

size Nil = 0
size (Node a Nil Nil) = 1
size (Node a left right) = 1 + size left + size right

-- sumTree :: BinTree -> Integer
sumTree Nil = 0
sumTree (Node a Nil Nil) = a
sumTree (Node a left right) = a + sumTree left + sumTree right

traverseDFS Nil = []
traverseDFS (Node a Nil Nil) = [a]
traverseDFS (Node a left right) = traverseDFS left ++ [a] ++ traverseDFS right

getLevel _ Nil = []
getLevel k (Node a left right) = if k == 0 then [a] else getLevel (k-1) left ++ getLevel (k-1) right

-- traverseBFS Nil = []
-- traverseBFS t = bst [t]
--     where bst [] = []
--           bst xs = let vals = [a | Node a _ _ <- xs]
--                        children = [child | Node _ l r <- xs, child <- [l,r], child /= Nil]
--                        in vals : bst children

traverseBFS Nil = []
traverseBFS (Node a Nil Nil) = [a]
traverseBFS (Node a left right) = a : traverseBFS left ++ traverseBFS right

mapTree f Nil = Nil
mapTree f (Node a Nil Nil) = Node (f a) Nil Nil
mapTree f (Node a left right) = Node (f a) (mapTree f left) (mapTree f right)


data NaryTree a = Root a [NaryTree a]
    deriving (Show, Eq, Ord)

constructMaxTree [] = Nil
constructMaxTree xs = let maxVal = maximum xs
                          (leftList, (_:rightList)) = break (== maxVal) xs
                          in Node maxVal (constructMaxTree leftList) (constructMaxTree rightList)


inOrder Nil = []
inOrder (Node val left right) = inOrder left ++ [val] ++ inOrder right

isSorted [] = True
isSorted [a] = True
isSorted (x:y:xs) = x < y && isSorted (y:xs)

isBST t = isSorted (inOrder t)

