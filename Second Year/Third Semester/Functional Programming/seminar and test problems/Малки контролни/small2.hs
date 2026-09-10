

generateStars = streamStars 0
    where streamStars n = (replicate n '*' ++ replicate n '+') : streamStars (n+1) 


-- >>> take 10 generateStars
-- ["","*+","**++","***+++","****++++","*****+++++","******++++++","*******+++++++","********++++++++","*********+++++++++"]

getPos matrix funcs = filter (>=0) (getValues matrix funcs)
    where getValues [] _ = []
          getValues _ [] = []
          getValues (row:rs) (f:fs) = map f row ++ getValues rs fs

-- >>> getPos [[0, -1], [0, 8], [4, 5]] [(+1), (\x -> x - 4), (/2)] 
-- [1.0,0.0,4.0,2.0,2.5]


data Nat = Zero | Succ Nat
  deriving (Eq, Ord, Show)

decToNat 0 = Zero
decToNat n = Succ (decToNat (n-1))

-- >>> decToNat 5
-- Succ (Succ (Succ (Succ (Succ Zero))))

subtractNat a Zero = a
subtractNat (Succ a) (Succ b) = subtractNat a b

-- >>> subtractNat (Succ (Succ (Succ Zero))) (Succ (Succ Zero))
-- Succ Zero


divNat _ Zero = Zero
divNat a (Succ Zero) = a
divNat (Succ a) b = solve (Succ a) b Zero
    where solve (Succ x) y count 
            | (Succ x) < y = count
            | otherwise = solve (subtractNat (Succ x) y) y (Succ count)

-- >>> divNat (Succ (Succ (Succ Zero))) (Succ (Succ Zero))
-- Succ Zero

-- >>> divNat (Succ (Succ (Succ (Succ Zero)))) (Succ Zero)
-- Succ (Succ (Succ (Succ Zero)))

-- >>> divNat (Succ (Succ (Succ (Succ (Succ Zero))))) (Succ (Succ Zero))
-- Succ (Succ Zero)

addNat Zero Zero = Zero
addNat a Zero = a
addNat Zero a = a
addNat (Succ a) b = Succ (addNat a b)


-- >>> addNat (Succ (Succ Zero)) (Succ (Succ (Succ Zero)))
-- Succ (Succ (Succ (Succ (Succ Zero))))

avgNat lst = solve lst (length lst)
    where solve [x] len = divNat x (decToNat len)  
          solve (x:y:xs) len = solve ((addNat x y):xs) len

-- >>> avgNat [(Succ (Succ (Succ Zero))), (Succ (Succ (Succ Zero))), (Succ Zero)]
-- Succ (Succ Zero)
