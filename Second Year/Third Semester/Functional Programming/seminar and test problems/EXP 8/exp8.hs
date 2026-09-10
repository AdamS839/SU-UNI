
(x1, y1) $$ (x2, y2) = sqrt (fromIntegral(x1 - x2)^2 + fromIntegral(y1 - y2)^2)

scalarProduct (x1, x2, x3) (y1, y2, y3) = x1*y1 + x2*y2 + x3*y3


map1 f [] = []
map1 f (x:xs) = f x ++ (map1 f xs)

filter1 p [] = []
filter1 p (x:xs) = if (p x) then x ++ filter1 p xs else filter1 p xs

foldrWr op nv [] = nv
foldrWr op nv (x:xs) = op x (foldrWr op nv xs)

join [] _ = []
join [x] _ = x
join (x:xs) ch = x ++ ch : join xs ch


isInfixOf2 [] _ = True
isInfixOf2 _ [] = False
isInfixOf2 (x:xs) (y:ys) = if x == y then isInfixOf2 xs ys else isInfixOf2 (x:xs) ys 

quicksort [] = []
quicksort (x:xs) = quicksort (filter (<x) xs) ++ [x] ++ quicksort (filter (>x) xs)

insert x [] = [x]
insert x (y:ys) 
    | x <= y = x : y : ys
    | otherwise = y : insert x ys

insertsort [] = []
insertsort (x:xs) = insert x (insertsort xs) 

longestSublist predicate (x:xs) = longPref [] [] predicate (x:xs)
    where   longPref curr best pred [] = if length best > length curr then best else curr
            longPref curr best pred (x:xs)
                | pred [x] = longPref (curr ++ [x]) best pred xs
                | otherwise = longPref [] (if (length best > length curr) then best else curr) pred xs


-- "Hello, my name is Rali" -> "Hello, my name is Ra"
-- [2, 4, 6, 7, 8, 0, 2, 4, 6, 1] -> [2,4,6]

longestPrefix pred list = iter list 
    where iter curr
            | pred curr = curr
            | otherwise = iter (init curr)


