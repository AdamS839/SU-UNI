

evenCubes [] = []
evenCubes (x:xs) = if even x then [x^3] ++ evenCubes xs else evenCubes xs

descartes xs ys = [(x,y) | x <- xs, y <- ys]

pair x list = map (\y -> (x, y)) list

descartes1 [] [] = []
descartes1 _ [] = []
descartes1 [] _ = []
descartes1 (x:xs) list = pair x list ++ descartes1 xs list

-- problem 4

addToListWords [] = []
addToListWords lst = addWords lst [] []
    where addWords [] listOfWords currWord = (if (currWord == []) then listOfWords else listOfWords ++ [currWord])
          addWords (x:xs) listOfWords currWord
            | x == ' ' || x == '.' = addWords xs (if (currWord == []) then listOfWords else listOfWords ++ [currWord]) []
            | otherwise = addWords xs listOfWords (currWord ++ [x])

countTimesFirst [] = 0
countTimesFirst [x] = 1
countTimesFirst (x:y:xs)
    | x == y = 1 + countTimesFirst (x:xs)
    | otherwise = countTimesFirst (x:xs)


histogram [] = []
histogram lst = histo (addToListWords lst) []
    where histo [] pairsLst = pairsLst
          histo (x:xs) pairslst = histo xs (pairslst ++ [(x, (countTimesFirst (x : xs)))])

ln (n1, n2) (y1, y2) = if (n2 >= y2) then (n1,n2) else (y1,y2)

mostCommonWord [] = ""
mostCommonWord lst = fst (foldr ln ("", 0) (histogram lst))


nats = 0 : map succ nats

repeat' a = a ++ repeat' a

fib = fibon 0 1
    where fibon a b = a : fibon b (a+b)

factorial 0 = 1
factorial n = n * factorial (n-1)

factList = facts 0
    where facts a = factorial a : facts (succ a)


subsets [] = [[]]
subsets (x:xs) = let ys = subsets xs in ys ++ map (x:) ys

{-
x = 1, xs = 2
subsets 2 => x = 2 xs = [] => subsets [] = [[]] => [[]] ++ 2 : [] = [[]], [2]

[[]] [2] ++ 1:[[]] , 1: [2]
-}

infsubset [] = [[]]
infsubset (x:xs) = [] : infs (x:xs) [[]]
    where infs (x:xs) allToNow = let updated = map (x:) allToNow 
                                 in updated ++ infs xs (allToNow ++ updated)

