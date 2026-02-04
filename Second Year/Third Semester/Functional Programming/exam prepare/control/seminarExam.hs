import Data.Text.Internal.Fusion (countChar)

-- problem 1

generatePowers k t = [ x | x <- [0..], onlyDivisors k t x]
                        where onlyDivisors k t x 
                                | x == 0 = False
                                | x `mod` k == 0 = onlyDivisors k t (x `div` k)
                                | x `mod` t == 0 = onlyDivisors k t (x `div` t)
                                | x == 1 = True
                                | otherwise = False

-- >>> take 20 (generatePowers 2 3)
-- [1,2,3,4,6,8,9,12,16,18,24,27,32,36,48,54,64,72,81,96]

-- problem 2

data BinTree a = Empty | Node a (BinTree a) (BinTree a)
    deriving (Eq, Ord, Show)

t = Node 1 (Node 2 Empty (Node 3 Empty Empty)) (Node 4 (Node 6 Empty Empty) Empty)

codeTree Empty p = Empty
codeTree (Node a l r) p = Node (a, p) (codeTree l (p++"0")) (codeTree r (p++"1"))

toBinary 0 = "0"
toBinary 1 = "1"
toBinary n = toBinary (n `div` 2) ++ show (n `rem` 2)

countCodes Empty = 0
countCodes (Node (x,p) l r)
 | toBinary x == p = 1 + countCodes l + countCodes r
 | otherwise = countCodes l + countCodes r
 
-- >>> codeTree t "1"
-- Node (1,"1") (Node (2,"10") Empty (Node (3,"101") Empty Empty)) (Node (4,"11") (Node (6,"110") Empty Empty) Empty)

-- >>> countCodes (codeTree t "1")
-- 3

-- problem 3

getAll [] _ = []
getAll _ [] = []
getAll (i:is) (f:fs) = map f i : getAll is fs


-- sequenceA (getAll [[1,2], [3,4], [5,7]] [(+3), id, (7-)])
-- sequenceA [[1,2], [3,4], [5,7]] 

zipHT is fs = zip (sequenceA is) (sequenceA (getAll is fs)) 


check [] = True
check [x] = True
check [x,y] = True
check (x:y:z:is) = x - y == y - z && check (y:z:is)

-- (i:is) -> check i

checkAll [] = []
checkAll ((h,t):is)
  | check t = h
  | otherwise = checkAll is

aProg is fs = checkAll $ zipHT is fs

-- >>> aProg [[1,2], [3,4], [5,7]] [(+3), id, (7-)]
-- [1,3,5]

-- aProg is fs = head [xs |  xs <- sequenceA is, check (zipWith ($) fs xs)]

-- problem 4

type Name = String
type Quantity = Integer
type Ingredients = [(Name, Quantity)]
type Med = (Name, Ingredients)


l = [
      ("A", [("p",5), ("q",3)]),
      ("B", [("p",4), ("q",3)]),
      ("C", [("p",3)])
    ]

isStronger (_, ingsA) (_, ingsB) = 
  let
      findQty name ings = if null [q | (n,q) <- ings, n == name] then 0 else head [q | (n,q) <- ings, n == name]

-- >>> findQty "p" [("p",5), ("q",3)]
-- 5

      hasAll = and [nameB `elem` map fst ingsA | (nameB,_) <- ingsB]

      allEnough = and [findQty nameB ingsA >= qtyB | (nameB, qtyB) <- ingsB]

      oneBigger = or [findQty nameB ingsA > qtyB | (nameB, qtyB) <- ingsB]

      in hasAll && allEnough && oneBigger

-- >>> isStronger (l !! 0) (l !! 1)
-- True

getNames l = [name | (name, q) <- l]

-- >>> getNames l
-- ["A","B","C"]

strongerThan medA l = [ (name, ings) | (name, ings) <- l, isStronger (name, ings) medA]

strongerThanName medA l = [ name | (name, ings) <- l, isStronger (name, ings) medA]

-- >>> strongerThan (l!!2) l
-- [("A",[("p",5),("q",3)]),("B",[("p",4),("q",3)])]

-- >>> strongerThanName (l!!2) l
-- ["A","B"]

-- >>> zip ["A","B","C"] [[], ["A"], ["A", "B"]]
-- [("A",[]),("B",["A"]),("C",["A","B"])]

getSubtraction [] = 0
getSubtraction ((_, q):ings) = abs (q - getSubtraction ings)  

getAddit medA medB = getSubtraction (snd medA) + getSubtraction (snd medB)

-- >>> getAddit ("A",[("p",5),("q",13)]) ("C", [("p",3)])
-- 11

-- >>> getAddit ("B",[("p",4),("q",3)]) ("C", [("p",3)])
-- 4

zipNameToSub medX l = zip (strongerThanName medX l) (map (getAddit medX) (strongerThan medX l))

-- >>> zipNameToSub (l!!2) l
-- [("A",5),("B",4)]

leastStrongest medX l = if null (zipNameToSub medX l) then "" else getMinimum (zipNameToSub medX l)
    where
        getMinimum [x] = fst x
        getMinimum ((n,q):(n1,q1):ns)
           | q <= q1 = getMinimum ((n,q):ns)
           | otherwise = getMinimum ((n1,q1):ns)

-- >>> leastStrongest (l!!2) l
-- "B"

strongRelation l = [ (med, strongerThanName med l) | med <- l]

-- >>> strongRelation l
-- [(("A",[("p",5),("q",3)]),[]),(("B",[("p",4),("q",3)]),["A"]),(("C",[("p",3)]),["A","B"])]

