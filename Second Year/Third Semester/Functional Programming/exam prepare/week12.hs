data Nat = Zero | Succ Nat
    deriving (Eq, Show, Ord)

minus' Zero Zero = Just Zero
minus' a Zero = Just a
minus' Zero (Succ _) = Nothing
minus' (Succ n) (Succ m) = minus' n m

find p [] = Nothing
find p (x:xs)
  | p x = Just x
  | otherwise = find p xs

lookup1 k [] = Nothing
lookup1 k ((key, val):other)
   | k == key = Just val
   | otherwise = lookup1 k other
