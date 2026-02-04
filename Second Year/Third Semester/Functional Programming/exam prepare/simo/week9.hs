
isNull [] = True
isNull _ = False

firstEl [x] = x
firstEl (x:_) = x
firstEl [] = error

-- removeFirst [x] = []
-- removeFirst (_:xs) = xs
-- removeFirst [] = error

fromXs n [] = []
fromXs n (x:xs)
 | n > 1 = fromXs (n - 1) xs
 | n == 1 = xs

concatenate [] rs = rs
concatenate (x:xs) rs = x : concatenate xs rs

join [] = []
join (xs:xss) = xs ++ join xss

checkRootLC [] = []
checkRootLC ((x,y):xs) = if x * x == y then True : checkRootLC xs else False : checkRootLC xs 

isPresent x [] = False
isPresent x (y:ys) 
  | x == y = True
  | otherwise = isPresent x ys

removeFirstLeft x [] = []
removeFirstLeft x (y:ys) 
  | x == y = ys
  | otherwise = y : removeFirstLeft x ys

removeAllEq x [] = []
removeAllEq x (y:ys)
  | x == y = removeAllEq x ys
  | otherwise = y : removeAllEq x ys

