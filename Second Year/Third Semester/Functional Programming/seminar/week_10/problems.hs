--problem 1

pitagoreanTripples = [(x,y,z) | z <- [1..], 
                                x <- [1..z], 
                                y <- [x..z], 
                                x^2 + y^2 == z^2,
                                gcd x y == 1]


-- problem 2

filterTupels p xs ys = [(xs !! i, ys !! j) | h <- [0..],
                                             i <- [0..h],
                                             let j = h - i,
                                             p (xs !! i) (ys !! j) ]

-- problem 3

taylorElem n x = x^n / fromIntegral (product [1..n])

-- taylorSeries x = map (\n -> taylorElem n x) [0..]
taylorSeries x = map (`taylorElem` x) [0..]

expTaylor x = sum (take 30 (taylorSeries x))

-- problem 4

--streamZipWith 

-- problem 5

-- problem 6
pr6 :: IO ()
pr6 = do
    putStrLn "Enter numbers"
    input <- getLine
    let nums = words input

    putStrLn  ("There are " ++ show (length nums) ++ " numbers.")

-- problem 7
pr7::IO()
pr7 = do
    putStrLn "Enter string:"
    input <- getLine
    let str = input

    putStrLn "Enter n times to repeat"
    n <- getLine
    let nrep = read n :: Int

    putStrLn (concat (replicate nrep str))

    