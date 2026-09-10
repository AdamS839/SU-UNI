

data Nat = Zero | Next (Nat)
    deriving (Show)

instance Eq Nat where
    Zero == Zero = True
    _ == Zero = False
    Zero == _ = False
    Next a == Next b = a == b

instance Ord Nat where
    Zero <= Zero = True
    Zero <= _ = True
    _ <= Zero = False
    Next a <= Next b = a <= b

-- instance Show Nat where
--     show Zero = show (0 :: Int)
--     show (Next a) = show num
--         where num = 1 + count a
--               count Zero = 0
--               count (Next b) = 1 + count b


plus Zero a = a
plus (Next a) b = Next (plus a b)

mult Zero _ = Zero
mult (Next a) b = plus b (mult a b)
-- (1+2) * 2 = 2 + (2 * 2)

natToInteger Zero = 0
natToInteger (Next a) = 1 + natToInteger a

integerToNat 0 = Zero
integerToNat a = Next (integerToNat (a-1))



data List a = Nil | Cons a (List a)
  deriving (Show)


mapList f Nil = Nil
mapList f (Cons a b) = Cons (f a) (mapList f b)

instance Foldable List where
    foldr op nv Nil = nv
    foldr op nv (Cons a b) = op a (foldr op nv b)

data BinTree a = Node a (BinTree a) (BinTree a) | Leaf

instance Eq a => Eq (BinTree a) where
    Leaf == Leaf = True
    Leaf == _ = False
    _ == Leaf = False
    Node a l1 r1 == Node b l2 r2 = a == b && l1 == l2 && r1 == r2

t = Node 1 (Node 2 (Node 3 (Node 4 Leaf Leaf) Leaf) Leaf) (Node 5 (Node 6 (Node 7 (Node 8 Leaf Leaf) (Node 9 Leaf Leaf)) (Node 10 Leaf Leaf)) Leaf)

instance Show a => Show (BinTree a) where
    show Leaf = "{}"
    show (Node a left right) = "(" ++ show a ++ " " ++ show left ++ " " ++ show right ++ ")"

instance Foldable BinTree where   
    foldr op nv Leaf = nv
    foldr op nv (Node x left right) = foldr op (op x (foldr op nv right)) left 

allPaths Leaf = []
allPaths (Node x Leaf Leaf) = [[x]]
allPaths (Node x left right) = map (x:) (allPaths left ++ allPaths right)


isElem x Leaf = False
isElem x (Node a left right)
    | x == a = True
    | otherwise = isElem x left || isElem x right

sumNums Leaf = 0
sumNums (Node x left right) = x + sumNums left + sumNums right

-- data Maybe a = Nothing | Just a
--   deriving (Show)

safeDiv _ 0 = Nothing
safeDiv x y = Just (x `quot` y, x `rem` y)

integerToNat' :: Int -> Maybe Nat
integerToNat' a
   | a < 0 = Nothing
   | otherwise = Just (craft a)
        where craft 0 = Zero
              craft a = Next (craft (a-1))


minus' Zero Zero = Just Zero
minus' Zero _ = Nothing
minus' a Zero = Just a 
minus' (Next a) (Next b) = minus' a b

-- >>> minus' (Next Zero) (Next (Next Zero))
-- Nothing
-- >>> minus' (Next (Next Zero)) (Next Zero)
-- Just (Next Zero)

find pred [] = Nothing
find pred (x:xs) = if (pred x) then Just x else find pred xs

-- >>> find even [1, 2, 3]
-- Just 2

-- >>> find even [1, 3]
-- Nothing

lookup' k [] = Nothing
lookup' k ((x,y):xs)
    | k == x = Just y
    | otherwise = lookup' k xs


-- >>> lookup' 1 [(1, "a"), (2, "b"), (1, "c")]
-- Just "a"

-- >>> lookup' 3 [(1, "a"), (2, "b"), (1, "c")]
-- Nothing


