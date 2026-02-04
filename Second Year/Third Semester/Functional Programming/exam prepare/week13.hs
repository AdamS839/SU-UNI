
data List a
 = Nil
 | Cons a (List a)
 deriving (Show, Foldable)

instance Functor List where
    fmap _ Nil = Nil
    fmap f (Cons x xs) = Cons (f x) (fmap f xs)

data BST a = Empty | NodeBST a (BST a) (BST a)
     deriving (Eq, Show, Ord)

instance Functor BST where
    fmap _ Empty = Empty
    fmap f (NodeBST x left right) = NodeBST (f x) (fmap f left) (fmap f right)

-- (NodeBST 6 (NodeBST 3 (NodeBST 1 Empty Empty) (NodeBST 5 Empty Empty)) (NodeBST 10 (NodeBST 7 Empty Empty) (NodeBST 12 Empty Empty)))

bstInsert x Empty = NodeBST x Empty Empty
bstInsert x (NodeBST v left right)
   | x < v = NodeBST v (bstInsert x left) right
   | otherwise = NodeBST v left (bstInsert x right)

bstSearch x Empty = False
bstSearch x (NodeBST v left right)
   | x == v = True
   | x < v = bstSearch x left
   | otherwise = bstSearch x right

bstValues Empty = []
bstValues (NodeBST x Empty Empty) = [x]
bstValues (NodeBST x left right) = bstValues left ++ [x] ++ bstValues right

bstSize Empty = 0
bstSize (NodeBST x Empty Empty) = 1
bstSize (NodeBST x left right) = 1 + bstSize left + bstSize right

bstSort xs = bstValues (foldr bstInsert Empty xs)

data Map k v = EmptyM | NodeM k v (Map k v) (Map k v)
     deriving (Show, Eq, Ord)

mapInsert ki vi EmptyM = NodeM ki vi EmptyM EmptyM
mapInsert ki vi (NodeM k v left right)
  | ki == k = NodeM k vi left right
  | ki < k = NodeM k v (mapInsert ki vi left) right
  | otherwise = NodeM k v left (mapInsert ki vi right)

mapSearch kl EmptyM = Nothing
mapSearch kl (NodeM k v left right)
  | kl == k = Just v
  | kl < k = mapSearch kl left
  | otherwise = mapSearch kl right

instance Functor (Map k) where
    fmap _ EmptyM = EmptyM
    fmap f (NodeM k v left right) = NodeM k (f v) (fmap f left) (fmap f right)

convToBool :: Map String Float -> Map String Bool
convToBool = fmap (>0)

data BinTree a = Leaf | NodeBT a (BinTree a) (BinTree a)
     deriving (Show, Eq, Ord)


mirror Leaf = Leaf
mirror (NodeBT x left right) = NodeBT x (mirror right) (mirror left)

-- (NodeBT 6 (NodeBT 3 (NodeBT 1 Leaf Leaf) (NodeBT 5 Leaf Leaf)) (NodeBT 10 (NodeBT 7 Leaf Leaf) (NodeBT 12 Leaf Leaf)))

isSym t = t == mirror t

data Expr = Var 
          | Const Double
          | Add Expr Expr
          | Sub Expr Expr 
          | Mul Expr Expr
          | Div Expr Expr
          | Pow Expr Expr
    deriving (Show, Eq, Ord)

eval Var x = x
eval (Const c) _ = c
eval (Add c1 c2) x = eval c1 x + eval c2 x
eval (Sub c1 c2) x = eval c1 x - eval c2 x
eval (Mul c1 c2) x = eval c1 x * eval c2 x
eval (Div c1 c2) x = eval c1 x / eval c2 x
eval (Pow c1 c2) x = eval c1 x ** eval c2 x

derive Var = Const 1
derive (Const _) = Const 0
derive (Add f1 f2) = Add (derive f1) (derive f2)
derive (Sub f1 f2) = Sub (derive f1) (derive f2)
derive (Mul f1 f2) = Add (Mul (derive f1) f2) (Mul f1 (derive f2))
derive (Div f1 f2) = Div (Sub (Mul (derive f1) f2) (Mul f1 (derive f2))) (Pow f2 (Const 2))
derive (Pow base (Const n)) = Mul (Mul (Const n) (Pow base (Const (n-1)))) (derive base)

expr =
  Sub
    (Add
      (Pow Var (Const 2))
      (Mul (Const 3) Var))
    (Const 5)

t = NodeBT 'c' (NodeBT 'a' (NodeBT 'b' Leaf Leaf)
                       (NodeBT 'a' Leaf Leaf))
             (NodeBT 'b' Leaf Leaf)

-- Да се напише функция labelTree :: Eq a => BTree a -> BTree Int, която заменя всеки елемент в дадено дърво с него
-- вата поредност на срещане при ляво-корен-дясно обхождане на дървото:

--     ┌──'c'──┐         ┌──3──┐
--  ┌─'a'─┐   'b'  ->  ┌─2─┐   1
-- 'b'   'a'           1   2

-- t :: Tree Char
-- t = Node 'c' (Node 'a' (Node 'b' Leaf Leaf)
--                        (Node 'a' Leaf Leaf))
--              (Node 'b' Leaf Leaf)

