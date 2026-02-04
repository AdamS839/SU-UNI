
-- data Maybe a
--   = Nothing
--   | Just a
--   deriving (Show)

data Nat -- от Natural number (естествено число)
  = Zero
  | Succ Nat
  deriving (Show, Eq, Ord)

safeDiv :: Int -> Int -> Maybe (Int, Int)
safeDiv _ 0 = Nothing
safeDiv x y = Just (x `quot` y, x `rem` y)


-- problem 1

integerToNat' :: Int -> Maybe Nat
integerToNat' n
  | n < 0 = Nothing
  | otherwise = Just (make n)
         where make 0 = Zero
               make q = Succ (make (q - 1))


-- problem 2

-- less Zero Zero = False
-- less Zero _ = True
-- less _ Zero = False
-- less (Succ a) (Succ b) = less a b

minus' p q
  | p <= q = Nothing
  | otherwise = Just (subtract1 p q)
        where subtract1 a Zero = a
              subtract1 (Succ a) (Succ b) = subtract1 a b
            
-- problem 3

find p l
  | not (any p l) = Nothing
  | otherwise = Just (head (filter p l))

-- problem 4

lookup' _ [] = Nothing
lookup' k ((key, val):xs) 
 | k == key = Just val
 | otherwise = lookup' k xs

-- lookup' k l
--   | null l = Nothing
--   | k == fst (head l) = Just (snd (head l))
--   | otherwise = lookup' k (tail l)