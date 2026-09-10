-- problem 1


generatePowers k t = [ x | x <- [0..], onlyDivisors k t x]
                        where onlyDivisors k t x 
                                | x == 0 = False
                                | x `mod` k == 0 = onlyDivisors k t (x `div` k)
                                | x `mod` t == 0 = onlyDivisors k t (x `div` t)
                                | x == 1 = True
                                | otherwise = False

-- >>> take 10 (generatePowers 2 3)
-- [1,2,3,4,6,8,9,12,16,18]

data BT a = Node a (BT a) (BT a) | Leaf
    deriving (Show, Eq, Ord)

t= (Node 1 (Node 2 
                Leaf 
                (Node 3 Leaf Leaf)) 
           (Node 4 
                (Node 6 Leaf Leaf) 
                Leaf)
    )

digits n
    | n < 0     = digits (-n)
    | n < 10    = 1
    | otherwise = 1 + digits (n `div` 10)

binaryToDec 0 = 0
binaryToDec 1 = 1
binaryToDec n = (n `div` 10^(digits n - 1)) * 2 ^ (digits n - 1) + binaryToDec (n `mod` 10^(digits n - 1))

binaryAdd number dig = number * 10 + dig

countCodes tree = counted tree 1
    where counted Leaf _ = 0
          counted (Node x left right) value
            | x == binaryToDec value = 1 + (counted left (binaryAdd value 0)) + (counted right (binaryAdd value 1))
            | otherwise = (counted left (binaryAdd value 0)) + (counted right (binaryAdd value 1))

-- >>> countCodes (Node 1 (Node 2 Leaf (Node 3 Leaf Leaf)) (Node 4 (Node 6 Leaf Leaf) Leaf))
-- 3

-- problem 3

isProg [] = True
isProg [x] = True
isProg [x,y] = True
isProg (x:y:z:xs) = y - x == z - y && isProg (y:z:xs)

getAll [] _ = []
getAll _ [] = []
getAll (l:ls) (f:fs) = map f l : getAll ls fs 

zipKeysVals ls fs = zip (sequenceA ls) (sequenceA (getAll ls fs))

checked [] = []
checked ((k,v):vs)
    | isProg v = k
    | otherwise = checked vs

aProg ls fs = checked $ zipKeysVals ls fs

-- >>> aProg [[1,2], [3,4], [5,7]] [(+3), id, (7-)]
-- [1,3,5]

-- problem 4



type Ingredient = [(String, Integer)]
type Name = String
type Medicine = (Name, Ingredient)

l :: [(Name, Ingredient)]     
l = [("A",[("p",5),("q",3)]),
     ("B",[("p",4),("q",3)]),
     ("C",[("p",3)])]


isStronger (_, t1) (_, t2) = 
    let 
        findQty name ings = if null [q | (n,q) <- ings, n == name] then 0 else (head [q | (n,q) <- ings, n == name])
        hasAll = and [nameB `elem` map fst t1 | (nameB,_) <- t2]
        allEnough = and [findQty nameB t1 >= qtyB | (nameB, qtyB) <- t2]
        oneBigger = or [findQty nameB t1 > qtyB | (nameB, qtyB) <- t2]
        in hasAll && allEnough && oneBigger

-- >>> isStronger (l !! 0) (l !! 1)
-- True


minPairInt [x] = x
minPairInt (x:y:xs)
    | snd x <= snd y = minPairInt (x:xs)
    | otherwise = minPairInt (y:xs)

leastStrongest (name, t1) l = 
    let 
        sumQty ings = if null [q | (n,q) <- ings] then 0 else  (sum [q | (n,q) <- ings])
        smallestDiff = fst $ minPairInt [ (n, (sumQty i) - (sumQty t1)) | (n,i) <- l, n /= name, isStronger (n,i) (name, t1) == True]
        in smallestDiff

-- >>> leastStrongest (l!!2) l
-- "B"


strongRelation l = 
    let
        formList =  [((l !! y), [fst (l !! i)]) | i <- [0..(length l - 1)], 
                                y <- [0..(length l - 1)],
                                i /= y,
                                isStronger (l!!i) (l!!y)]
        conjure [] = []
        conjure (x:xs) =
            let
                same = [snd y | y <- xs, fst y == fst x]
                rest = [y | y <- xs, fst y /= fst x]
            in
                (fst x, snd x ++ concat same) : conjure rest
        putNotIn [] conjured = conjured
        putNotIn (x:xs) conjured = if x `elem` (map fst conjured) then putNotIn xs conjured else (x, []) : putNotIn xs conjured
        in putNotIn l (conjure formList)



-- >>> strongRelation l
-- [(("A",[("p",5),("q",3)]),[]),(("B",[("p",4),("q",3)]),["A"]),(("C",[("p",3)]),["A","B"])]

fslll (x:xs) = fst x
