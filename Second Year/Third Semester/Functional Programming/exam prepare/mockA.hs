
somos k = xs
  where 
    xs = replicate k 1 ++ [findNext num | num <- [k..]]
    findNext num = (sum [xs !! (num - i) * xs !! (num + i - k) | i <- [1..k `div` 2]]) `div` (xs !! (num - k))

-- xs = [x1,x2,x3,x4,x5] -> x5 = (x4*x2 + x3*x3) / x1 => x5 = (xs[3]*xs[1] + xs[2]*xs[2]) `div` xs[0] = xs[4]  

-- >>> take 20 (somos 4)
-- [1,1,1,1,2,3,7,23,59,314,1529,8209,83313,620297,7869898,126742987,1687054711,47301104551,1123424582771,32606721084786]


cycles fs xs ind = go ind xs
    where
        go index [x] = x
        go index (x:xs) = (fs !! index) x (go ((index + 1) `mod` length fs) xs)

findMin fs xs = minimum (map (cycles fs xs) [0..length fs - 1])

-- >>> cycles [(+),(-),(*)] [1,2] 0
-- 3

-- >>> findMin [(+),(-),(*)] [1,2,0,3,-1]
-- -7

