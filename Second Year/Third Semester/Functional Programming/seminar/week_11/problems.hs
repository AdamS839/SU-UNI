data List a
  = Nil
  | Cons a (List a) 
instance Show a => Show (List a) where
 show Nil = []
 show (Cons x xs) = show x ++ " " ++ show xs

data Nat = Zero | Next Nat

instance Eq Nat where
    Zero == Zero = True
    _ == Zero = False
    Zero == _ = False
    Next a == Next b = a == b

instance Ord Nat where
    Zero <= Zero = True
    Zero <= _ = False
    _ <= Zero = False
    Next a <= Next b = a <= b

instance Show Nat where
    show Zero = show (0 :: Int)
    show (Next a) = show num
        where num = 1 + count a
              count Zero = 0
              count (Next b) = 1 + count b 


plus Zero a = a
plus (Next a) b = Next (plus a b)

mult Zero _ = Zero
mult _ Zero = Zero
mult (Next a) b = plus b (mult a b) 

natToInteger Zero = 0
natToInteger (Next x) = 1 + natToInteger x

integerToNat 0 = Zero
integerToNat x = Next (integerToNat (x - 1))

-- problem 2.1

mapList _ Nil = Nil
mapList f (Cons x xs) = Cons (f x) (mapList f xs)

-- problem 2.2
instance Foldable List where
   foldr _ nv Nil = nv
   foldr f nv (Cons x xs) = f x (foldr f nv xs)

-- problem 3

data BTree a = Node a (BTree a) (BTree a) | Leaf

instance Eq a => Eq (BTree a) where
    Leaf == Leaf = True
    Leaf == _ = False
    _ == Leaf = False
    Node a left right == Node b left2 right2 = a == b && left == left2 && right == right2 

-- complete later
--instance Show (BTree a) => Show (BTree a) where



    
