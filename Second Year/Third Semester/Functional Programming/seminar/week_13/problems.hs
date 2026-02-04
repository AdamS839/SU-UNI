
data List a = 
   Nil
 | Cons a (List a)
 deriving (Show, Foldable)

instance Functor List where
    fmap _ Nil = Nil
    fmap f (Cons x xs) = Cons (f x) (fmap f xs)

-- example: fmap (*2) Cons 1 (Cons 2 (Cons 3 Nil))

data BST a
   = Empty
   | Node a (BST a) (BST a)
   deriving (Show, Eq, Ord)

instance Functor BST where
    fmap _ Empty = Empty
    fmap f (Node x left right) = (Node (f x) (fmap f left) (fmap f right))

bstInsert v Empty = (Node v Empty Empty)
bstInsert v (Node x left right)
    | v < x = Node x (bstInsert v left) right
    | v >= x = Node x left (bstInsert v right)

-- example: bstInsert 20 (Node 5 (Node 4 (Node 1 Empty Empty) Empty) (Node 9 (Node 6 Empty Empty) Empty))

bstSearch v Empty = False
bstSearch v (Node x left right)
    | v == x = True
    | v < x = bstSearch v left
    | v > x = bstSearch v right

bstValues Empty = []
bstValues (Node x Empty Empty) = [x]
bstValues (Node x left right) = bstValues left ++ [x] ++ bstValues right 

bstSize Empty = 0
bstSize (Node x left right) = bstSize left + 1 + bstSize right

bstSort xs = bstValues (foldr bstInsert Empty xs)

-- buildBST [] = []
-- buildBST (x:xs) = bstInsert x (buildBST xs)
-- bstSort xs = bstValues (buildBST xs)

data Map k v =
    EmptyM
    | NodeM k v (Map k v) (Map k v)
    deriving (Show, Eq, Ord)

mapInsert k v EmptyM = (NodeM k v EmptyM EmptyM)
mapInsert k v (NodeM sk sv left right)
    | k == sk = NodeM sk v left right
    | k < sk = NodeM sk sv (mapInsert k v left) right
    | otherwise = NodeM sk sv left (mapInsert k v right)

-- example: mapInsert 8 2304 (NodeM 4 1 (NodeM 1 2456 EmptyM EmptyM) (NodeM 9 123 EmptyM EmptyM))

mapSearch k EmptyM = Nothing
mapSearch k (NodeM sk sv left right)
    | k > sk = mapSearch k right
    | k < sk = mapSearch k left
    | otherwise = Just sv 

-- example:  mapSearch 9 (NodeM 4 1 (NodeM 1 2456 EmptyM EmptyM) (NodeM 9 123 EmptyM EmptyM))

instance Functor (Map k) where
    fmap _ EmptyM = EmptyM
    fmap f (NodeM k v left right) = NodeM k (f v) (fmap f left) (fmap f right)

convertToBool :: Map String Float -> Map String Bool
convertToBool = fmap (>0)

data BTree a = EmptyBT | NodeBT a (BTree a) (BTree a)
   deriving (Show, Eq, Ord)
