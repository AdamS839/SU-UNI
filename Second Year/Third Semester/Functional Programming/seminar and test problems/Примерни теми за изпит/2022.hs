


segments (x:xs) = solve x [x] xs 
    where 
          solve prev curr (y:ys)
            | prev > y = solve y (curr ++ [y]) ys
            | otherwise = curr : solve y [y] ys

-- >>> take 7 (segments [1,5,3,2,2,6,4,7, 60, 30, 1, 2, 3])
-- [[1],[5,3,2],[2],[6,4],[7],[60,30,1],[2]]


fillSegments [] = []
fillSegments [a] = [a,a-1..0]
fillSegments (x:y:xs)
    | x > y && x /= y+1 = x : fillSegments ((x-1):y:xs)
    | x <= y && x /= 0   = x : fillSegments ((x-1):y:xs)
    | otherwise         = x : fillSegments (y:xs)

-- >>> fillSegments [1,5,3,2,2,6,4,7, 6, 4, 1, 3]
-- [1,0,5,4,3,2,1,0,2,1,0,6,5,4,3,2,1,0,7,6,5,4,3,2,1,0,3,2,1,0]

-- >>> take 27 (fillSegments [0..])
-- [0,1,0,2,1,0,3,2,1,0,4,3,2,1,0,5,4,3,2,1,0,6,5,4,3,2,1]

-- >>> take 30 (fillSegments [2,4..])
-- [2,1,0,4,3,2,1,0,6,5,4,3,2,1,0,8,7,6,5,4,3,2,1,0,10,9,8,7,6,5]


-- Problem 2

tom room = (room + 1) `mod` 3

house = [(0, [1, 2]), (1, [0, 2]), (2, [0, 1, 3]), (3, [2])]


getEdgesVert pos [] = []
getEdgesVert pos ((x,y):xs)
    | pos == x = y
    | otherwise = getEdgesVert pos xs

-- >>> getEdgesVert 3 house
-- [2]

-- >>> getEdgesVert 2 house
-- [0,1,3]

spike graph start tomFunc tomStart = solve graph start (tomFunc tomStart) [start]
    where solve graph start tomPos spikePath
            | (bfs1 start tomPos) == tomPos = spikePath ++ [tomPos]
            | otherwise = solve graph (bfs1 start tomPos) (tomFunc tomPos) (spikePath ++ [bfs1 start tomPos])
          bfs1 spike tom = bfsinit spike tom [spike] [[spike]] graph
            where bfsinit spikePos tomPos visited queue graph
                        | last (head queue) == tomPos = if length (head queue) == 1 then (head queue) !! 0 else (head queue) !! 1
                        | otherwise =
                            let 
                                currNode = head queue
                                item = last currNode
                                newVisited = [vert | vert <- (getEdgesVert item graph), vert `notElem` visited]
                                newPaths = [currNode ++ [x] | x <- newVisited]
                                visitedNew = visited ++ newVisited
                                newQueue = tail queue ++ newPaths 
                                in bfsinit spikePos tomPos visitedNew newQueue graph

-- >>> spike house 3 tom 2
-- [3,2,1]

-- >>> spike house 3 tom 0
-- [3,2,2]

-- Problem 3

getCurr lst = getWord lst
    where getWord [] = []
          getWord (x:xs) = zip (fst x) (snd x) ++ getWord xs

wordLen lst = solve lst
    where solve ((x,y):xs) = length x

-- >>> getCurr [("cat", "+-+"), ("use", "?--")]
-- [('c','+'),('a','-'),('t','+'),('u','?'),('s','-'),('e','-')]

getNotIn lst = notin (getCurr lst) []
    where notin [] miss = (miss)
          notin (x:xs) miss
            | snd x == '-' = notin xs (miss ++ [fst x])
            | otherwise = notin xs miss

-- >>> getNotIn [("cat", "+-+"), ("use", "?--")]
-- "ase"

getMightBe lst = usedin (getCurr lst) [([],0)] (wordLen lst - 1) 0
    where usedin [] use num pos = (filter (\(x,y) -> x /= []) use)
          usedin (x:xs) use num pos 
            | snd x == '?' = usedin xs (use ++ [([fst x], pos)]) num (if pos == num then 0 else pos + 1)
            | otherwise = usedin xs use num (if pos == num then 0 else pos + 1)

-- >>> getMightBe [("cat", "--+"), ("use", "?--"), ("gal", "??-")]
-- [("u",0),("g",0),("a",1)]

getPosPlus lst = plusses (getCurr lst) [([],0)] (wordLen lst - 1) 0
    where plusses [] use num pos = (filter (\(x,y) -> x /= []) use)
          plusses (x:xs) use num pos 
            | snd x == '+' = plusses xs (use ++ [([fst x], pos)]) num (if pos == num then 0 else pos + 1)
            | otherwise = plusses xs use num (if pos == num then 0 else pos + 1)

-- >>> getPosPlus [("cat", "+-+"), ("use", "?--")]
-- [("c",0),("t",2)]

searchByValue [] _ = []
searchByValue ((x,y):xs) num 
    | num == y = x
    | otherwise = searchByValue xs num

-- >>> searchByValue [("c",0),("t",2)] 0
-- "c"

containsForbidden [] checks = False
containsForbidden (x:xs) checks
    | x `elem` checks = True
    | otherwise = containsForbidden xs checks

-- >>> containsForbidden "cat" "ase"
-- True

-- >>> (getMightBe [("cat", "+-+"), ("use", "?--")])
-- [("u",0)]


-- wordle [] = "no solution"
wordle lst = case generate (wordLen lst) of
        [] -> "no solution"
        [x] -> x
        _ -> "many solutions"
    where generate n = filter valid (gen n 0)
            where gen 0 _ = [[]]
                  gen n pos = [x : word | x <- ['a'..'z'], word <- gen (n-1) (pos+1), 
                                containsForbidden [x] (getNotIn lst) == False,
                                [x] /= (searchByValue (getMightBe lst) pos),
                                [x] == (searchByValue (getPosPlus lst) pos) || (searchByValue (getPosPlus lst) pos) == ""
                              ]   
                  valid word = all (\(letter, pos) -> head letter `elem` word && word !! pos /= head letter) (getMightBe lst)


-- >>> wordle [("cat", "+-+"), ("use", "?--")]
-- "cut"

-- >>> wordle [("cat", "???"), ("dog", "--+")]
-- "no solution"

-- >>> wordle [("dog", "?--"), ("dad", "?++")]
-- "many solutions"
