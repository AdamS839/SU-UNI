
-- problem 1
--($$) :: Num a => (a,a) -> (a,a) -> a
($$) :: (Float, Float) -> (Float, Float) -> Float
(x1, y1) $$ (x2, y2) = sqrt ((x1 - x2)^2 + (y1 - y2)^2)


-- problem 2
scalarProduct _ (0,0,0) = 0
scalarProduct (0,0,0) _ = 0
scalarProduct (x1,x2,x3) (y1,y2,y3) = x1*y1 + x2*y2 + x3*y3

-- problem 3
foldr2 :: (a -> b -> b) -> b -> [a] -> b
foldr2 _ nv [] = nv
foldr2 f nv (x:xs) = foldr2 f (f x nv) xs

--filter

filter2 _ [] = []
filter2 p (x:xs)
        | p x       = x : filter2 p xs
        | otherwise = filter p xs

--map
map2 _ [] = []
map2 f (x:xs) = f x : map2 f xs

-- problem 4
join [] _ = []
join (x:xs) ch = x ++ [ch] ++ join xs ch 

-- problem 5

len [] = 0
len (x:xs) = 1 + len xs

isInfixOf _ [] = False
isInfixOf [] _ = True
--isInfixOf (x:xs) (y:ys) = x == y && take (len (x:xs)) (y:ys) == (xs) || isInfixOf (x:xs) ys
isInfixOf xs (y:ys) = isPrefix xs (y:ys) || isInfixOf xs ys
   where isPrefix [] _ = True
         isPrefix _ [] = False
         isPrefix (x:xs) (y:ys) = x == y && isPrefix xs ys

-- problem 6
-- quickSort

quickSort [] = []
quickSort (x:xs) = quickSort (filter (<= x) xs) ++ [x] ++ quickSort (filter (> x) xs)

-- problem 7
-- insertionSort

-- problem 8
