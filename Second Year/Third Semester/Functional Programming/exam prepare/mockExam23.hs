-- problem 1 A

somos k = xs
    where
        xs = replicate k 1 ++ [next n | n <- [k..]]
        next n = (sum [xs !! (n - i) * xs !! (n-k+i) | i <- [1.. k `div` 2]]) `div` (xs !! (n - k))

-- >>> take 10 (somos 4)
-- [1,1,1,1,2,3,7,23,59,314]

-- problem 1 B

prime n = if n > 1 then null [x | x <- [2 .. n - 1], n `mod` x == 0] else False
          -- (n > 1) && null [x | x <- [2 .. n - 1], n `mod` x == 0]

primeList = [ x | x <- [2..], prime x] 

madeFromPrime n k
   | k == 1 = prime n
   | otherwise = or [madeFromPrime (n `div` p) (k - 1) | p <- takeWhile (<=n) primeList, n `mod` p == 0]

primitive k = [ x | x <- [k..], madeFromPrime x k]


-- problem 2 A

type Q = [Integer]
type T = [(Integer, Char, Integer)]
type F = [Integer]

type Q0 = Integer

type NFA = (Q, Q0, T, F)

-- {0, 1, 2}, 0, {(0,a,1),(1,b,1),(1,a,2),(2,a,2),(2,b,1)}, {0, 1, 2}
a :: NFA
a = ([0,1,2], 0, [(0,'a',1), (1, 'b', 1), (1, 'a', 2), (2, 'a', 2), (2,'b',1)], [0,1,2])

-- accept (states, start, links, finals) word = travel start word
--    where 
--        travel q [] = q `elem` finals
--        travel q (c:cs) = or [travel q' cs | (from, ch, q') <- links, from == q, ch == c]


nextStates (_, _, links, _) q c = [q' | (from, ch, q') <- links, from == q, ch == c]

move nfa states c = concatMap (\q -> nextStates nfa q c) states

accepts nfa@(_, start, _, accepting) word = 
    any (`elem` accepting) (process nfa [start] word)
  where
    process _ states [] = states
    process nfa states (c:cs) =
        let next = move nfa states c
        in if null next then [] else process nfa next cs

wordsOfLength 0 = [""]
wordsOfLength n = [c:word | c <- ['a','b'], word <- wordsOfLength (n-1)]

allWordsUpTo n = concatMap wordsOfLength [0..n]

rejectedWord nfa@(states, _, _, _) = 
    findRejected nfa 0 (length states)
  where

    findRejected nfa len maxLen
        | len > maxLen = Nothing  -- Съгласно упътването
        | otherwise = 
            case findFirstRejected (allWordsUpTo len) of
                Just word -> Just word
                Nothing -> findRejected nfa (len+1) maxLen
    
    findFirstRejected [] = Nothing
    findFirstRejected (word:words)
        | not (accepts nfa word) = Just word
        | otherwise = findFirstRejected words

-- problem 2 B


a2 = ([0, 1, 2, 3], 0, [(0,'a',1),(1,'b',1),(0,'a',2),(0,'b',2),(2,'a',3)], [0, 2, 3])

-- rightWords nfa@(states, start, links, final)= findWords nfa (allWordsUpTo (length states))
--    where findWords nfa (w:ws)
          
--           | accepts nfa w = w : findWords nfa ws
--           | otherwise = findWords nfa ws


-- problem 3 A

cyclic fs xs ind = go ind xs
    where 
        go index [x] = x
        go index (x:xs) = (fs !! index) x (go ((index + 1) `mod` length fs) xs)

-- findMin fs xs = minimum (map (cyclic fs xs) [0..length fs - 1])


applyFunc fs [x] _ = x
applyFunc fs (x:y:xs) start = 
    let f = fs !! (start `mod` length fs)
    in f x (applyFunc fs (y:xs) (start + 1))

-- findMin fs is =  minimum [applyFunc fs is i | i <- [0..length fs]]

-- >>> findMin [(+),(-),(*)] [1,2,0,3,-1]
-- -7

-- findMin fs xs = minimum [ applyCyclic fs xs i | i <- [0..length fs - 1] ]

-- problem 3 B

findMax fs xs = maximum [ applyFunc fs xs i | i <- [0..length fs - 1] ]

-- >>> findMax [(+),(*),(-)] [2,5]
-- 10


-- problem 4 A

type Name = [Char]
type PromisePoints = Integer
type RealPoints = Integer

type Game = [(Name, PromisePoints, RealPoints)]

getR [] = []
getR ((n,pp,rp):xs) = (n, rp, abs (pp - rp)) : getR xs 

insertByError x [] = [x]
insertByError x@(n1,r1,e1) (y@(n2,r2,e2):ys)
  | e1 <= e2 = x : y : ys
  | otherwise = y : insertByError x ys

sortByError [] = []
sortByError (x:xs) = insertByError x (sortByError xs)

-- >>> sortByError (getR [("Angel",14,15),("Andrei",8,10),("Atanas",10,3),("Georgi",6,4)])
-- [("Angel",15,1),("Andrei",10,2),("Georgi",4,2),("Atanas",3,7)]

-- >>> reverse (sortByError (getR [("Angel",14,15),("Andrei",8,10),("Atanas",10,3),("Georgi",6,4)]))
-- [("Atanas",3,7),("Georgi",4,2),("Andrei",10,2),("Angel",15,1)]
 
makePair [] = []
makePair xs = zip xs (reverse xs)

-- >>> makePair (sortByError (getR [("Angel",14,15),("Andrei",8,10),("Atanas",10,3),("Georgi",6,4)]))
-- [(("Angel",15,1),("Atanas",3,7)),(("Andrei",10,2),("Georgi",4,2)),(("Georgi",4,2),("Andrei",10,2)),(("Atanas",3,7),("Angel",15,1))]


makeScore [] = []
makeScore ((x@(n1,p1,e1),y@(n2,p2,e2)):xs) = (n1, p1+e2) : makeScore xs

-- >>> makeScore (makePair (sortByError (getR [("Angel",14,15),("Andrei",8,10),("Atanas",10,3),("Georgi",6,4)])))
-- [("Angel",22),("Andrei",17),("Georgi",11),("Atanas",3)]

-- >>> getR [("Angel",14,15),("Andrei",8,10),("Atanas",10,3),("Georgi",6,4)]
-- [("Angel",15,1),("Andrei",10,2),("Atanas",3,7),("Georgi",4,2)]

finalScore [] = []
finalScore game = makeScore $ makePair $ sortByError $ getR game

-- >>> finalScore [("Angel",14,15),("Andrei",8,10),("Atanas",10,3),("Georgi",6,4)]
-- [("Angel",22),("Andrei",12),("Georgi",6),("Atanas",4)]

-- problem 4 B

makePairR [] = []
makePairR xs = zip (reverse xs) xs

-- >>> sortByError $ getR [("Deqn",10,14),("Eslin",5,8),("Maria",11,10),("Martin",1,6)]
-- [("Maria",10,1),("Eslin",8,3),("Deqn",14,4),("Martin",6,5)]

-- >>> makePairR $ sortByError $ getR [("Deqn",10,14),("Eslin",5,8),("Maria",11,10),("Martin",1,6)]
-- [(("Martin",6,5),("Maria",10,1)),(("Deqn",14,4),("Eslin",8,3)),(("Eslin",8,3),("Deqn",14,4)),(("Maria",10,1),("Martin",6,5))]

makeScoreR [] = []
makeScoreR ((x@(n1,p1,e1),y@(n2,p2,e2)):xs) = (n2, p2+e1) : makeScoreR xs

finalScoreReverse [] = []
finalScoreReverse game = makeScoreR $ makePairR $ sortByError $ getR game

-- >>> finalScoreReverse [("Deqn",10,14),("Eslin",5,8),("Maria",11,10),("Martin",1,6)]
-- [("Maria",15),("Eslin",12),("Deqn",17),("Martin",7)]

