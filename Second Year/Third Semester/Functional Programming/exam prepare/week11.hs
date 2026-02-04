data List a = Nil | Cons a (List a)
    deriving (Show, Eq, Ord)  

data Nat = Zero | Succ Nat
     deriving (Show)

instance Eq Nat where
    Zero == Zero = True
    _ == Zero = False
    Zero == _ = False
    Succ a == Succ b = a == b

instance Ord Nat where
    Zero <= _ = True
    _ <= Zero = False
    Succ a <= Succ b = a <= b

plus a Zero = a
plus Zero a = a
plus (Succ a) b = plus a (Succ b)

mult _ Zero = Zero
mult Zero _ = Zero
mult (Succ a) b = plus b (mult a b)

natToInt Zero = 0
natToInt (Succ a) = natToInt a + 1

intToNat 0 = Zero
intToNat a = Succ (intToNat (a - 1))

mapList _ Nil = Nil
mapList f (Cons x xs) = Cons (f x) (mapList f xs)

instance Foldable List where
    foldr _ nv Nil = nv
    foldr f nv (Cons x xs) = f x (foldr f nv xs)

data BTree a = Leaf | Node a (BTree a) (BTree a)
    deriving (Eq)

instance Show a => Show (BTree a) where
    show Leaf = ""
    show (Node x left right) = "(" ++ show x ++ " " ++ show left ++ " " ++ show right ++ ")"

instance Foldable BTree where
    foldr _ nv Leaf = nv
    foldr f nv (Node x left right) = foldr f (f x (foldr f nv right)) left

t = Node 1 (Node 2 (Node 3 (Node 4 Leaf Leaf) Leaf) Leaf) (Node 5 (Node 6 (Node 7 (Node 8 Leaf Leaf) (Node 9 Leaf Leaf)) (Node 10 Leaf Leaf)) Leaf)

allPaths Leaf = []
allPaths (Node x Leaf Leaf) = [[x]]
allPaths (Node x left right) = map (x:) (allPaths left ++ allPaths right)

memberTree r Leaf = False
memberTree r (Node x Leaf Leaf) = r == x
memberTree r (Node x left right) = r == x || memberTree r left || memberTree r right

sumTree Leaf = 0
sumTree (Node x Leaf Leaf) = x
sumTree (Node x left right) = x + sumTree left + sumTree right

integerToNat' :: Int -> Maybe Nat
integerToNat' 0 = Just Zero
integerToNat' z
    | z < 0 = Nothing
    | otherwise = Just (Succ (intToNat (z - 1)))


lookup1 k [] = Nothing
lookup1 k ((key, val):other)
   | k == key = Just val
   | otherwise = lookup1 k other