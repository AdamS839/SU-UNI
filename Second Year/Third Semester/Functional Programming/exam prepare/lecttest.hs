
module Functor where


import Prelude hiding (Functor, fmap, (<$>),
                       Applicative, pure, (<*>))

-- >>> liftA2 (*) [2,3] [1,2,3,4]
-- [2,4,6,8,3,6,9,12]

-- >>> pure 5
-- 5


pure1 a = return a

-- >>> pure1 5
-- 5

class Functor f where
   fmap :: (a -> b) -> f a -> f b
   fmap = (<$>)

   (<$>) :: (a -> b) -> f a -> f b
   (<$>) = fmap

instance Functor Maybe where
    fmap _ Nothing = Nothing
    fmap f (Just x) = Just $ f x

instance Functor ((,) a) where
    f <$> (x, y) = (x, f y)

-- >>> (*2) <$> (1, 3)
-- (1,6)

newtype ReversedPair a b = ReversedPair (b, a)
    deriving (Show)

instance Functor (ReversedPair b) where
    fmap f (ReversedPair (x, y)) = ReversedPair (f x, y)

-- >>> fmap (*2) (ReversedPair (3,4))
-- ReversedPair (6,4)

instance Functor (Either a) where
    _ <$> Left x = Left x
    f <$> Right y = Right $ f y

-- >>> (+5) <$> Left "error"
-- Left "error"

-- >>> (+5) <$> Right 4
-- Right 9

instance Functor [] where
    fmap = map

-- >>> fmap (+4) [1,2,3,4]
-- [5,6,7,8]

data BinTree a = Empty | Node { root :: a, left, right :: BinTree a}
    deriving (Show, Eq, Ord, Read)

leafBin x = Node x Empty Empty
t = Node 1 (leafBin 3) (leafBin 5)

depth :: BinTree a -> Integer
depth Empty = 0
depth (Node _ left right) = 1 + max (depth left) (depth right)

-- >>> depth t
-- 2

leaves Empty = []
leaves (Node val Empty Empty) = [val]
leaves (Node val left right) = leaves left ++ leaves right

-- >>> leaves t
-- [3,5]

mapBinTree _ Empty = Empty
mapBinTree f (Node val left right) = Node (f val) (mapBinTree f left) (mapBinTree f right)

instance Functor BinTree where
    fmap = mapBinTree

-- >>> fmap (*2) t
-- Node {root = 2, left = Node {root = 6, left = Empty, right = Empty}, right = Node {root = 10, left = Empty, right = Empty}}

instance Functor IO where
    fmap f io = do x <- io
                   return $ f x

class Functor f => Applicative f where
    pure :: a -> f a
    (<*>) :: f (a -> b) -> f a -> f b
    -- fmap = (<*>) . pure

instance Applicative Maybe where
    pure = Just
    Nothing <*> _ = Nothing
    _ <*> Nothing = Nothing
    Just f <*> Just x = Just $ f x

-- >>> (+) <$> Just 2 <*> Just 5 
-- Just 7

instance Applicative (Either a) where
    pure = Right
    Left x <*> _ = Left x
    _ <*> Left x = Left x
    Right f <*> Right x = Right $ f x

-- >>> (+) <$> Right 2 <*> Right 7
-- Right 9

-- >>> (*) <$> Left "error" <*> Right 1
-- Left "error"

instance Applicative [] where
    pure x = [x]
    fs <*> xs = [f x | f <- fs, x <- xs]

-- >>> (*) <$> [1,2,3] <*> [11,22,33]
-- [11,22,33,22,44,66,33,66,99]

instance Functor ((->) r) where
    fmap = (.)

instance Applicative ((->) r) where
  pure = const
  (f <*> g) x = f x (g x)

-- >>> ((+) <$> (*2) <*> (^3)) 3
-- 33

-- >>> sequenceA [Just 2, Nothing, Just 5]
-- Nothing

-- >>> sequenceA [Just 3, Just 6, Just 93]
-- Just [3,6,93]

-- >>> sequenceA [Right 4, Right 5, Right 34]
-- Right [4,5,34]
-- >>> sequenceA [Right 4, Right 5, Left "error"]
-- Left "error"
