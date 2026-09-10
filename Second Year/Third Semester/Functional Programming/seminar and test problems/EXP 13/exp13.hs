

data List a = Nil | Cons a (List a)
    deriving (Show, Ord, Eq, Foldable)

instance Functor List where
    fmap _ Nil = Nil
    fmap f (Cons a b) = Cons (f a) (fmap f b)

-- >>> fmap (*2) (Cons 1 (Cons 2 (Cons 3 Nil)))
-- Cons 2 (Cons 4 (Cons 6 Nil))


data BST a = Node a (BST a) (BST a) | Leaf
    deriving (Show, Eq, Ord, Foldable)

t = Node 5
        (Node 2
            (Node 1 Leaf Leaf)
            (Node 3
                Leaf
                (Node 4.5 Leaf Leaf)))
        (Node 8
            (Node 6
                Leaf
                (Node 7 Leaf Leaf))
            (Node 9
                Leaf
                (Node 10 Leaf Leaf)))


tSym = Node 5
        (Node 2
            (Node 1 Leaf Leaf)
            (Node 3
                Leaf
                (Node 4.5 Leaf Leaf)))
        (Node 2
            (Node 3
                (Node 4.5 Leaf Leaf)
                Leaf)
            (Node 1 Leaf Leaf))

instance Functor BST where
    fmap _ Leaf = Leaf
    fmap f (Node x left right) = Node (f x) (fmap f left) (fmap f right)


bstInsert a Leaf = Node a Leaf Leaf
bstInsert a (Node x left right)
    | a > x = Node x left (bstInsert a right)
    | a < x = Node x (bstInsert a left) right
    | otherwise = Node x left right


bstSearch a Leaf = False
bstSearch a (Node x left right)
    | a < x = bstSearch a left
    | a > x = bstSearch a right
    | otherwise = True

bstValues Leaf = []
bstValues (Node x left right) = bstValues left ++ [x] ++ bstValues right

bstSize Leaf = 0
bstSize (Node x left right) = (1 :: Int)+ bstSize left + bstSize right

bstSort [] = []
bstSort lst = bstValues (foldl (\tree x -> bstInsert x tree) Leaf lst)


data Map k v = NodeM k v (Map k v) (Map k v) | LeafM
    deriving (Show, Eq, Ord, Foldable)

testMap =
    NodeM 5 "five"
        (NodeM 2 "two"
            (NodeM 1 "one" LeafM LeafM)
            (NodeM 3 "three" LeafM LeafM))
        (NodeM 8 "eight"
            (NodeM 7 "seven" LeafM LeafM)
            (NodeM 10 "ten" LeafM LeafM))


-- testMap1 :: Map String Float
tested =
    NodeM "five" 5.0
        (NodeM "two" (-2.42)
            (NodeM "one" (-0.000000000001) LeafM LeafM)
            (NodeM "three" 3.0 LeafM LeafM))
        (NodeM "eight" 8.0
            (NodeM "seven" (-0.014425) LeafM LeafM)
            (NodeM "ten" (-10.23) LeafM LeafM))

mapInsert key val LeafM = NodeM key val LeafM LeafM
mapInsert key val (NodeM a b left right)
    | key == a = NodeM a val left right
    | key < a = NodeM a b (mapInsert key val left) right
    | otherwise = NodeM a b left (mapInsert key val right)

-- >>> mapInsert 4 "testtest" testMap
-- NodeM 5 "five" (NodeM 2 "two" (NodeM 1 "one" LeafM LeafM) (NodeM 3 "three" LeafM (NodeM 4 "testtest" LeafM LeafM))) (NodeM 8 "eight" (NodeM 7 "seven" LeafM LeafM) (NodeM 10 "ten" LeafM LeafM))

mapSearch key LeafM = Nothing
mapSearch key (NodeM k v left right)
    | key == k = Just v
    | key < k = mapSearch key left
    | otherwise = mapSearch key right

-- >>> mapSearch 4 testMap
-- Nothing

-- >>> mapSearch 10 testMap
-- Just "ten"


instance Functor (Map k) where
    fmap f LeafM = LeafM
    fmap f (NodeM k v left right) = NodeM k (f v) (fmap f left) (fmap f right)

getAssoc LeafM = LeafM
getAssoc (NodeM k v left right) = if v >= 0 then NodeM k 1 (getAssoc left) (getAssoc right)
                                            else NodeM k 0 (getAssoc left) (getAssoc right)

-- >>> getAssoc tested
-- NodeM "five" 1 (NodeM "two" 0 (NodeM "one" 0 LeafM LeafM) (NodeM "three" 1 LeafM LeafM)) (NodeM "eight" 1 (NodeM "seven" 0 LeafM LeafM) (NodeM "ten" 0 LeafM LeafM))

isSym Leaf Leaf = True
isSym (Node v left right) (Node s left1 right1)
    | v == s = (isSym left right1) && (isSym right left1)
    | otherwise = False

isSymHead Leaf = True
isSymHead (Node a left right) = isSym left right

-- >>> isSymHead t
-- False

-- >>> isSymHead tSym
-- True


data Expr = X | Const Double | Add Expr Expr
                      | Sub Expr Expr
                      | Mul Expr Expr
                      | Div Expr Expr
                      | Pow Expr Expr
    deriving (Show, Eq, Ord)

f = Mul (Add X (Const 3)) (Sub X (Const 2))

eval X x = x
eval (Const a) x = a
eval (Add e1 e2) x = (eval e1 x) + (eval e2 x)
eval (Sub e1 e2) x = (eval e1 x) - (eval e2 x)
eval (Mul e1 e2) x = (eval e1 x) * (eval e2 x)
eval (Div e1 e2) x = (eval e1 x) / (eval e2 x)
eval (Pow e1 e2) x = (eval e1 x) ** (eval e2 x)

derive X = Const 1
derive (Const a) = Const 0
derive (Add e1 e2) = Add (derive e1) (derive e2)
derive (Sub e1 e2) = Sub (derive e1) (derive e2)
derive (Mul e1 e2) = Add (Mul (derive e1) e2) (Mul e1 (derive e2)) 
derive (Div e1 e2) = Div (Sub (Mul (derive e1) e2) (Mul e1 (derive e2))) (Pow e2 (Const 2))
-- derive (Pow e1 e2) = Mul (Pow e1 e2) (Mul (derive e2) (log e1)) -- NO LOGARITHM

-- derive (Pow e1 e2) = 


tr = Node 'c' (Node 'a' (Node 'b' Leaf Leaf)
                       (Node 'a' Leaf Leaf))
             (Node 'b' Leaf Leaf)

getlrr Leaf = []
getlrr (Node x left right) = getlrr left ++ [x] ++ getlrr right

getunique [] = []
getunique (x:xs) = x : getunique (filter (\ y -> y /= x) xs)

mapVals [] _ = []
mapVals (x:xs) a = (x, a) : mapVals xs (succ a)

combinedWay tr = mapVals (getunique (getlrr tr)) 1

searchVal a [] = 0
searchVal a ((x,y):xs) = if a == x then y else searchVal a xs 

labelTree tree = labels tree (combinedWay tree)
    where labels Leaf vals = Leaf
          labels (Node x left right) vals = Node (searchVal x vals) (labels left vals) (labels right vals)