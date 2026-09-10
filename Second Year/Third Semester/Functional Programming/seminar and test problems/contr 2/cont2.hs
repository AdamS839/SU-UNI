
-- Problem 1

finDecRats = [(p,q) | s <- [2..], q <- [1..s-1],
                      let p = s - q,
                      gcd p q == 1,
                      hasOnlyTwoFive q,
                      fromIntegral p / fromIntegral q > 0]
    where hasOnlyTwoFive 1 = True
          hasOnlyTwoFive n
            | n `mod` 2 == 0 = hasOnlyTwoFive (n `div` 2)
            | n `mod` 5 == 0 = hasOnlyTwoFive (n `div` 5)
            | otherwise = False

-- >>> take 20 finDecRats
-- [(1,1),(2,1),(1,2),(3,1),(4,1),(3,2),(1,4),(5,1),(1,5),(6,1),(5,2),(3,4),(2,5),(7,1),(3,5),(8,1),(7,2),(5,4),(4,5),(1,8)]



-- Problem 3

type Purchases = [(Integer, String, Integer)]

s = [(1,"A",10),(1,"B",5),(2,"A",15),(3,"A",6),(3,"A",10),(4,"B",10),(5,"B",5),(6,"B",6)]

maxDay [(a, _, _)] = a
maxDay ((a,b,c):(x,y,z):xs)
    | c >= z = maxDay ((a,b,c):xs)
    | otherwise = maxDay ((x,y,z):xs)

-- >>> maxDay s
-- 2

getUniqueSellers lst = unique (getSellers lst)
    where unique [] = []
          unique (x:xs) = x : unique (filter (\y -> x /=y) xs)
          getSellers [] = []
          getSellers ((a,b,c):xs) = b : getSellers xs

-- >>> getUniqueSellers s
-- ["A","B"]

getDiffDaysSeller purchases seller = (length (unique (getOnlyFromSeller purchases seller)), seller)
    where getOnlyFromSeller [] s = []
          getOnlyFromSeller ((a,b,c):xs) s
            | b == s = (a,b,c) : getOnlyFromSeller xs s
            | otherwise = getOnlyFromSeller xs s
          unique [] = []  
          unique ((a,b,c):xs) = (a,b,c) : unique (filter (\(x,y,z) -> x /= a) xs)

-- >>> getDiffDaysSeller s "A"
-- (3,"A")

topShop s = snd $ foldl (\(accX,accY) (currX,currY) -> if accX >= currX then (accX,accY) else (currX,currY)) (head [getDiffDaysSeller s seller | seller <- getUniqueSellers s]) 
                [getDiffDaysSeller s seller | seller <- getUniqueSellers s]

-- >>> topShop s
-- "B"

getOnlyFromSeller [] s = []
getOnlyFromSeller ((a,b,c):xs) s
    | b == s = (a,b,c) : getOnlyFromSeller xs s
    | otherwise = getOnlyFromSeller xs s

upperGrowUnique [] = []
upperGrowUnique ((a,b,c):xs) = (a,b,c) : upperGrowUnique (filter (\ (x,y,z) -> x > a) xs)

-- >>> getOnlyFromSeller s "A"
-- [(1,"A",10),(2,"A",15),(3,"A",6),(3,"A",10)]

-- >>> upperGrowUnique (getOnlyFromSeller s "A")
-- [(1,"A",10),(2,"A",15),(3,"A",6)]

-- >>> upperGrowUnique [(1,"B",5),(4,"B",10),(5,"B",5),(6,"B",6)]
-- [(1,"B",5),(4,"B",10),(5,"B",5),(6,"B",6)]

getSequence lst = getConsecutive lst [] []
    where getConsecutive [] curr best = if length best >= length curr then length best else length curr 
          getConsecutive ((a,b,c):xs) ((x,y,z):crrs) best = if a == x + 1 then getConsecutive xs ((a,b,c):(x,y,z):crrs) best else getConsecutive xs ((x,y,z):crrs) best
          getConsecutive ((a,b,c):(x,y,z):xs) curr best 
                | a + 1 == x = getConsecutive ((x,y,z):xs) ((a,b,c) : curr) best
                | otherwise = getConsecutive ((x,y,z):xs) [] (if length best >= length curr then best else curr)

-- >>> getSequence (upperGrowUnique (getOnlyFromSeller s "A"))
-- 3

streak lst = maximum [getSequence (upperGrowUnique (getOnlyFromSeller lst seller)) | seller <- getUniqueSellers lst]

-- >>> streak s
-- 3
