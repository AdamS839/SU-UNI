

outsideCircle x y r =
    concat
        [ [(a-b,b) | b <- [0..a], (x-(a-b))^2 + (y-b)^2 > r^2] ++
          [(-b,a-b) | b <- [1..a], (x-(-b))^2 + (y-(a-b))^2 > r^2] ++
          [(-b,b-a) | b <- [a-1,a-2..1], (x-(-b))^2 + (y-(b-a))^2 > r^2] ++ 
          [(a-b,-b) | b <- [a,a-1..1], (x-(a-b))^2 + (y-(-b))^2 > r^2] 
           | a <- [0..] ]

-- >>> take 20 (outsideCircle 0 0 2)
-- [(3,0),(2,1),(1,2),(0,3),(-1,2),(-2,1),(-3,0),(-2,-1),(-1,-2),(0,-3),(1,-2),(2,-1),(4,0),(3,1),(2,2),(1,3),(0,4),(-1,3),(-2,2),(-3,1)]

data DeepList a = Atom a | List [DeepList a]
    deriving (Show, Eq, Ord)

deepMapCond xs p f1 f2 = iter xs 1
    where iter [] _ = []
          iter (Atom x : xs) d = if (p x d) then (Atom (f1 x d)) : iter xs d else (Atom (f2 x d)) : iter xs d
          iter (List a : xs) d = (List (iter a (d + 1))) : iter xs d

-- >>> (deepMapCond [Atom 1, List [Atom 2, List [Atom 5, Atom 1], Atom 4], Atom 3] (>) (\ x d -> d) (\ x d -> x * 2))
-- [Atom 2,List [Atom 4,List [Atom 3,Atom 2],Atom 2],Atom 1]


season = [("Silverstone", [("Leclerc", 15, 10, 82), ("Hamilton", 25, 5, 80), ("Verstappen", 18, 0, 78)]),
          ("Monza", [("Sainz", 18, 0, 81), ("Hamilton", 15, 10, 79), ("Verstappen", 25, 0, 77)]),
          ("Spa", [("Norris", 18, 5, 78), ("Russell", 25, 0, 76)]) ]

winners [] = []
winners ((x,lst):xs) = (x, foldl (\(n1, p1, pen1, t1) (n2, p2, pen2, t2) -> if (p1 >= p2) then (n1, p1, pen1, t1) else (n2, p2, pen2, t2) ) (head lst) lst) 
    : winners xs

allWinners lst = getSeconds (winners lst)
    where   getSeconds [] = []
            getSeconds ((x,(n,p,pen,t)):xs) = n : getSeconds xs

-- >>> allWinners season
-- ["Hamilton","Verstappen","Russell"]

sortBySec [] =[]
sortBySec ((n1,pen1):xs) = sortBySec (filter (\ (n,pen) -> pen1 < pen) xs) ++ [(n1, pen1)] ++ sortBySec (filter (\ (n,pen) -> pen1 >= pen) xs)

getPenalties [] = []
getPenalties ((x, lst):xs) = [(name,pen) | (name, points, pen, time) <- lst, pen > 0] ++ getPenalties xs

sumPenalties [] = []
sumPenalties ((x,y):xs) = 
    let 
        same = [snd g | g <- xs, fst g == x]
        rest = [g | g <- xs, fst g /= x]
        in (x, sum (y : same)) : sumPenalties rest

penaltyImpact lst = sortBySec $ sumPenalties $ getPenalties lst

-- >>> penaltyImpact season
-- [("Hamilton",15),("Leclerc",10),("Norris",5)]

getLaps [] = []
getLaps ((x,lst):xs) = (x, foldl (\ (n1, p1, pen1, t1) (n2, p2, pen2, t2) -> if (t1 <= t2) then (n1, p1, pen1, t1) else (n2, p2, pen2, t2)) (head lst) lst) : getLaps xs

getFastestLap lst = foldl (\ (n1, p1, pen1, t1) (n2, p2, pen2, t2) -> if t1 <= t2 then (n1, p1, pen1, t1) else (n2, p2, pen2, t2)) (head lst) lst


getFirstName (name, points, penalty, time) = name

fastestLap lst = getFirstName (getFastestLap $ (map snd (getLaps lst))) 

-- >>> fastestLap season
-- "Russell"

-- >>> winners season
-- [("Silverstone",("Hamilton",25,5,80)),("Monza",("Verstappen",25,0,77)),("Spa",("Russell",25,0,76))]

-- >>> (getLaps season)
-- [("Silverstone",("Verstappen",18,0,78)),("Monza",("Verstappen",25,0,77)),("Spa",("Russell",25,0,76))]

missedFastestLapWins lst = solve (winners lst) (getLaps lst)
    where solve [] _ = []
          solve _ [] = []
          solve ((x,y):xs) ((a,b):ys)
            | y == b = solve xs ys
            | otherwise = x : solve xs ys

-- >>> missedFastestLapWins season
-- ["Silverstone"]
