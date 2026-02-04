
(x1, y1) $$ (x2, y2) = sqrt ((x1 - x2)^2 + (y1 - y2)^2)


scalarProduct (x1,x2,x3) (y1,y2,y3) = x1*y1 + x2*y2 + x3*y3

map1 f [] = []
map1 f l = f (head l) : map1 f (tail l)

filter1 p [] = []
filter1 p l = if p (head l) then head l : filter1 p (tail l)
                            else filter1 p (tail l)

foldr' op nv [] = nv
foldr' op nv (x:xs) = op x (foldr' op nv xs)


join [] _ = ""
join [x] _ = x
join (x:xs) ch = x ++ [ch] ++ join xs ch


isInfixOf [] _ = True
isInfixOf _ [] = False
-- isInfixOf (x:xs) (y: ys) = x == y && isInfixOf xs ys || isInfixOf (x:xs) ys 
isInfixOf l (y:ys) = isPrefixOf l (y:ys) || isInfixOf l ys
    where isPrefixOf [] _ = True
          isPrefixOf _ [] = False
          isPrefixOf (x:xs) (y:ys) = x == y && isPrefixOf xs ys


quickSort [] = []
quickSort (x:xs) = quickSort (filter (<= x) xs) ++ [x] ++ quickSort (filter (>= x) xs)

insert n [] = [n]
insert n (x:xs)
  | n <= x = n : (x:xs)
  | otherwise = x : insert n xs


insertionSort [] = []
insertionSort (x:xs) = insert x (insertionSort xs)

-- insertionSort xs = foldr insert [] xs

-- Get it

longestPrefix p xs = helper p xs [] []
    where helper p [] prefix maxPrefix = maxPrefix
          helper p (y:ys) prefix maxPrefix = let newPrefix = prefix ++ [y]
            in if p newPrefix then helper p ys newPrefix newPrefix else helper p ys newPrefix maxPrefix

longestSublist :: ([a] -> Bool) -> [a] -> [a]
longestSublist p [] = []
longestSublist p (x:xs) = let lhs = longestPrefix p (x:xs)
                              rhs = longestSublist p xs 
            in if length lhs >= length rhs then lhs else rhs 