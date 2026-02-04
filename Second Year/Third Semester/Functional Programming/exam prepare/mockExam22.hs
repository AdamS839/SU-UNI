
-- problem 1

segments [] = []
segments [x] = [[x]]
segments (x:y:xs)
  | x > y = (x : head (segments (y:xs))) : tail (segments (y:xs))
  | otherwise = [x] : segments (y:xs)


-- >>> segments [1,5,3,2,2,6,4,7]
-- [[1],[5,3,2],[2],[6,4],[7]]


fillSegments xs = concatMap fill $ segments xs
        where
            fill (a:_) = [a, a-1 ..0]

-- >>> fillSegments [1,5,3,2,2,6,4,7]
-- [1,0,5,4,3,2,1,0,2,1,0,6,5,4,3,2,1,0,7,6,5,4,3,2,1,0]


-- problem 2

-- nah

-- problem 3 

getRes ([], _) = []
getRes (_, []) = []
getRes (word, res)
  | head res == '+' = head word : getRes (tail word, tail res)
  | head res == '-' = '*' : getRes (tail word, tail res)
  | head res == '?' = '?' : head word : getRes (tail word, tail res)
  | otherwise = getRes (tail word, tail res) 

-- >>> getRes ("cat", "+-+")
-- "c*t"

-- >>> getRes ("use", "?--")
-- "?u**"

getAllRes xs = map getRes xs

-- >>> getAllRes [("cat", "+-+"), ("use", "?--")]
-- ["c*t","?u**"]

allWords n = sequence (replicate n ['a'..'z'])

-- >>> allWords 3

matches word (guess, feedback) = all check (zip3 word guess feedback)
  where
    check (w, g, '+') = w == g
    check (w, g, '-') = g `notElem` word
    check (w, g, '?') = w /= g && g `elem` word


filterWords moves =
  let n = length (fst (head moves))
  in filter (\w -> all (matches w) moves) (allWords n)

wordle moves =
  case filterWords moves of
    []  -> "no solution"
    [w] -> w
    _   -> "many solutions"

-- >>> wordle [("cat", "+-+"), ("use", "?--")]
-- "cut"

-- >>> wordle [("cat", "???"), ("dog", "--+")]
-- "no solution"

-- >>> wordle [("dog", "?--"), ("dad", "?++")]
-- "many solutions"

