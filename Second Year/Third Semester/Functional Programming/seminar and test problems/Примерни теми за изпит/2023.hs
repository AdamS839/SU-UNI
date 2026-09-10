
-- problem 1

next window = if (length window /= 0) then solveObhvad window `div` head window else 0
    where solveObhvad [] = 0
          solveObhvad (x:xs)
            | length xs == 0 = 0
            | length xs == 1 = head xs * head xs
            | otherwise = head xs * last xs + solveObhvad (x : tail (init xs))

somos 0 = []
somos n = replicate (n) 1 ++ solve (replicate n 1) 
    where solve curr = next curr : solve (tail curr ++ [next curr])

-- >>> take 10 (somos 4)
-- [1,1,1,1,2,3,7,23,59,314]

-- >>> take 30 (somos 6)
-- [1,1,1,1,1,1,3,5,9,23,75,421,1103,5047,41783,281527,2534423,14161887,232663909,3988834875,45788778247,805144998681,14980361322965,620933643034787,16379818848380849,369622905371172929,20278641689337631649,995586066665500470689,72559962302147228286849,3168992022738213982117009]

unique [] = []
unique (x:xs) = x : unique (filter (\y -> x /= y) xs)

-- >>> unique [1,2,3,2,3,5,1,1,2]
-- [1,2,3,5]

-- problem 2

type Automaton = ([Integer], Integer, [(Integer, Char, Integer)], [Integer])

a1 :: Automaton
a1 = ([0,1,2], 0, [(0,'a',1),(1,'b',1),(1,'a',2),(2,'a',2),(2,'b',1)], [0,1,2])

isWordIn [] _ = False
isWordIn transitions finals = last transitions `elem` finals

getTransits (_, _, lst, _) = lst
getStart (_ , a, _, _) = a
getFinals (_, _, _, fin) = fin

getAlphabet aut = alphabet (getTransits aut) []
    where alphabet [] lst = unique lst
          alphabet ((p,a,q):xs) lst = alphabet xs (lst ++ [a])


transitionNextPos _ _ [] = (-1)
transitionNextPos a s ((p,b,q):ts)
    | s == p && a == b = q
    | otherwise = transitionNextPos a s ts


getWordPath [] _ _ = []
getWordPath _ [] _ = []
getWordPath lst word start = generate word start lst
    where generate [] _ _ = []
          generate (x:xs) start transits = if transitionNextPos x start transits == -1 then [-1] else transitionNextPos x start transits 
            : generate xs (transitionNextPos x start transits) transits 

-- >>> getWordPath [(0,'a',1),(1,'b',1),(1,'a',2),(2,'a',2),(2,'b',1)] "aba" 0
-- [1,1,2]

-- >>> getWordPath [(0,'a',1),(1,'b',1),(1,'a',2),(2,'a',2),(2,'b',1)] "baaa" 0
-- [-1]

-- >>> isWordIn (getWordPath [(0,'a',1),(1,'b',1),(1,'a',2),(2,'a',2),(2,'b',1)] "baaa" 0) [0,1,2]
-- False

getWordMaxLen (a, _, _, _) = length a

wordsA 0 = [""]
wordsA n = [ c : w | c <- "ab", w <- wordsA (n-1)]

allWords n = concat [wordsA k | k <- [1..n]]

rejectedWord aut = case findRejected (allWords (getWordMaxLen aut)) of 
        [x] -> x
        [] -> "everything is accepted"
    where allWords n = concat [wordsA k | k <- [1..n]]
          wordsA 0 = [""]
          wordsA n = [ c : w | c <- (getAlphabet aut), w <- wordsA (n-1)]
          findRejected [] = [] 
          findRejected (x:xs)
            | isWordIn (getWordPath (getTransits aut) x (getStart aut)) (getFinals aut) = findRejected xs
            | otherwise = [x]

-- >>> findRejected ["a","b","aa","ab","ba","bb","aaa","aab","aba","abb","baa","bab","bba","bbb"]
-- "b"

-- >>> rejectedWord a1
-- "b"

a2 = ([0,1,2], 0, [(0,'a',1),(1,'b',1),(1,'a',2),(2,'a',2),(2,'b',1),(0,'b',1)], [0,1,2])

-- >>> rejectedWord a2
-- "everything is accepted"

-- Problem 3


rotations 0 _ = []
rotations n xs = xs : rotations (n-1) (tail xs ++ [head xs])

-- >>> rotations 3 ["+","-","*"]
-- [["+","-","*"],["-","*","+"],["*","+","-"]]

foldrbet fcs nums = gen fcs nums
    where gen _ [x] = x
          gen (f:fs) (x:xs) = f x (gen (fs ++ [f]) (xs))

findMin fcs nums = minimum [foldrbet fs nums | fs <- rotations (length fcs) fcs]

-- >>> findMin [(+),(-),(*)] [1,2,0,3,-1]
-- -7


foldrpet fcs nums = gen fcs (cycle nums)
    where gen [f] (x:y:_) = f x y
          gen (f:fs) (x:y:ys) = f x (gen fs (y:ys))

findMax fcs nums = maximum [foldrpet fcs num | num <- rotations (length nums) nums]

-- >>> findMax [(+),(*),(-)] [2,5]
-- 11

type Game = [(String, Integer, Integer)]

game = [("Angel",14,15),("Andrei",8,10),("Atanas",10,3),("Georgi",6,4)]

getMistakeRealPoints [] = []
getMistakeRealPoints ((a,b,c):xs) = (a, (abs (b - c)), c) : getMistakeRealPoints xs

-- >>> getMistakeRealPoints game
-- [("Angel",1,15),("Andrei",2,10),("Atanas",7,3),("Georgi",2,4)]

sortByHighestPoint [] = []
sortByHighestPoint ((a,b,c):xs) = sortByHighestPoint (filter (\(x,y,z) -> y <= b) xs) ++ [(a,b,c)] ++ sortByHighestPoint (filter (\(x,y,z) -> y > b) xs)

-- >>> sortByHighestPoint (getMistakeRealPoints game)
-- [("Angel",1,15),("Georgi",2,4),("Andrei",2,10),("Atanas",7,3)]

rewardPoints (_, a, _) = a


rewardWinners players = reward players (length players - 1)
    where reward [] _ = []
          reward ((a,b,c):xs) n = (a,b, c + (rewardPoints (players !! n))) : reward xs (n - 1)

-- >>> rewardWinners (sortByHighestPoint (getMistakeRealPoints game))
-- [("Angel",1,22),("Georgi",2,6),("Andrei",2,12),("Atanas",7,4)]

finalScores lst = sortAgain (solve (rewardWinners (sortByHighestPoint (getMistakeRealPoints lst))))
    where solve [] = []
          solve ((a,b,c):xs) = (a,c) : solve xs
          sortAgain [] = []
          sortAgain ((a,b):xs) = sortAgain (filter (\(x,y) -> y > b) xs) ++ [(a,b)] ++ sortAgain (filter (\(x,y) -> y <= b) xs)

-- >>> finalScores game
-- [("Angel",22),("Andrei",12),("Georgi",6),("Atanas",4)]

game1 = [("Angel",14,15),("Andrei",8,10),("Atanas",10,3)]

-- >>> finalScores game1
-- [("Angel",22),("Andrei",12),("Atanas",4)]
