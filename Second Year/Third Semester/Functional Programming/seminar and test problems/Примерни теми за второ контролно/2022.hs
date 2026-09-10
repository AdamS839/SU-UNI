-- Problem 1

sort [] = []
sort (x:xs) = sort (filter (<x) xs) ++ [x] ++ sort (filter (>x) xs)


isNPerm n f = sort (map f [0..n-1]) == [0..n-1]

-- >>> isNPerm 3 (\x -> (3 - x) `mod` 3) 
-- True

-- >>> isNPerm 10 (`div` 2) 
-- False

-- >>> isNPerm 10 (\x -> (x + 2) `mod` 10) 
-- True

maxCycle n f = findMax 0 [] []
    where findMax x visited best
            | sort visited == [0..n-1] = best
            | x `elem` visited = findMax (x + 1) visited best
            | otherwise = findMax (x + 1) (((findCycle x x [])) ++ visited) (if (length best) >= (length (findCycle x x [])) then best else (findCycle x x []))
                where 
                      findCycle start curr path
                        | f curr == start = [start] ++ path
                        | otherwise = findCycle start (f curr) (path ++ [(f curr)])

-- >>> maxCycle 3 (\x -> (3 - x) `mod` 3)
-- [1,2]

-- >>> maxCycle 10 (\x -> (x + 2) `mod` 10)
-- [0,2,4,6,8]

-- >>> maxCycle 10 (\x -> (x + 3) `mod` 10)
-- [0,3,6,9,2,5,8,1,4,7]


movingAverage lst n = iter lst n
    where 
          iter (x:xs) n = (fromIntegral (round (((sum (take n (x:xs))) / fromIntegral n) * 10)) / 10) : iter xs n

allAverages lst = solve lst 2
    where 
          solve lst n = movingAverage lst n : solve lst (n + 1) 

-- >>> map (take 6) (take 5 (allAverages [0.0..]))
-- [[0.5,1.5,2.5,3.5,4.5,5.5],[1.0,2.0,3.0,4.0,5.0,6.0],[1.5,2.5,3.5,4.5,5.5,6.5],[2.0,3.0,4.0,5.0,6.0,7.0],[2.5,3.5,4.5,5.5,6.5,7.5]]

-- Problem 3

inv = [ ("docs", ["ids", "invoices"]), ("ids", ["passport"]),  ("invoices", []), ("memes", []),
        ("family", ["new year", "birthday"]), ("funny", ["memes"]), ("pics", ["family", "funny"]) ]


getSupposeObj lst = concat [snd x | x <- lst]
getFirsts lst = [fst x | x <- lst]

allObjects [] = []
allObjects lst = getObj (getSupposeObj lst) (getFirsts lst)
    where getObj [] _ = []
          getObj (x:xs) boxes
            | x `elem` boxes = getObj xs boxes
            | otherwise = x : getObj xs boxes

-- >>> allObjects inv
-- ["passport","new year","birthday"]

getBoxes key [] = []
getBoxes key (x:xs) = if key == (fst x) then snd x else getBoxes key xs

-- >>> getBoxes "family" inv
-- ["new year","birthday"]

checkIfEmptyBox itemName lst
    | itemName `elem` ([fst x | x <- lst]) = check (getBoxes itemName lst)
    | otherwise = False
        where check [] = True
              check (x:xs) = checkIfEmptyBox x lst && (check xs)   

cleanUp lst = check lst lst
    where check [] _ = []
          check ((x,y):xs) origin
            | checkIfEmptyBox x origin == True = check xs origin
            | otherwise = (x, checkFurther y origin) : check xs origin
            where checkFurther [] _ = []
                  checkFurther (y:ys) lst
                    | checkIfEmptyBox y lst == True = checkFurther ys lst
                    | otherwise = y : checkFurther ys lst

-- >>> cleanUp inv
-- [("docs",["ids"]),("ids",["passport"]),("family",["new year","birthday"]),("pics",["family"])]
