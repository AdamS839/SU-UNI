
-- Problem 2

type Fixing = [(String, Double, String)]

fixing = [("USD",1.85,"BGN"), ("EUR",1.95,"BGN"), ("GBP",2.3,"BGN")]


convert (p,c) search [] = (p,c)
convert (p,c) search ((x,y,z):xs)
    | search == x && c == z = (p / y, search)
    | search == z && c == x = (p * y, search)
    | otherwise = convert (p,c) search xs

-- >>> convert (20,"BGN") "EUR" fixing
-- (10.256410256410257,"EUR")

-- >>> convert (20,"EUR") "BGN" fixing
-- (39.0,"BGN")

unique [] = []
unique ((a,b):xs) = (a,b) : unique (filter (\(x,y) -> (a,b) /= (x,y)) xs)

-- >>> unique [("USD","BGN"), ("EUR","BGN"), ("GBP","BGN"),("USD","BGN"),("USD","BGN")]
-- [("USD","BGN"),("EUR","BGN"),("GBP","BGN")]

craftGraph lst = unique [(c1,c2) | (c1,p,c2) <- lst] ++ unique [(c2,c1) | (c1,p,c2) <- lst]

-- >>> craftGraph fixing
-- [("USD","BGN"),("EUR","BGN"),("GBP","BGN"),("BGN","USD"),("BGN","EUR"),("BGN","GBP")]

neighbors _ [] = []
neighbors key ((c1,c2):xs)
    | key == c1 = c2 : neighbors key xs
    | otherwise = neighbors key xs

-- >>> neighbors "USD" (craftGraph fixing)
-- ["BGN"]

getPath fixing start end = solve (craftGraph fixing) [start] [[start]]
    where 
          solve graph visited queue
            | last (head queue) == end = head queue
            | otherwise = 
                let 
                    currPath = head queue
                    current = last currPath
                    newPaths = [currPath ++ [x] | x <- neighbors current graph]
                    visitNew = visited ++ [x | x <- neighbors current graph, x `notElem` visited]
                    in solve graph visitNew ((tail queue) ++ newPaths)

-- >>> getPath fixing "USD" "EUR"
-- ["USD","BGN","EUR"]

convertIt conv end fixing = iter conv (getPath fixing (snd conv) end)
    where iter (p,c) [] = (p,c)
          iter (p,c) (x:xs) = iter (convert (p,c) x fixing) xs

-- >>> convertIt (10,"USD") "EUR" fixing
-- (9.487179487179487,"EUR")

convertAll [] _ _ = []
convertAll (x:xs) end fixing = (convertIt x end fixing) : convertAll xs end fixing

-- >>> convertAll [(10,"USD"),(20,"GBP")] "EUR" fixing
-- [(9.487179487179487,"EUR"),(23.58974358974359,"EUR")]

-- Problem 3

allStats _ [] _ = []
allStats potok (x:xs) funcs = iter (take x potok) funcs : allStats (drop x potok) xs funcs
    where iter interval [] = []
          iter interval (f:fs) = [f interval] ++ iter interval fs

-- >>> take 10 (allStats [1..] (2:3:[1..]) [sum,length,maximum])
-- [[3,2,2],[12,3,5],[6,1,6],[15,2,8],[30,3,11],[54,4,15],[90,5,20],[141,6,26],[210,7,33],[300,8,41]]
