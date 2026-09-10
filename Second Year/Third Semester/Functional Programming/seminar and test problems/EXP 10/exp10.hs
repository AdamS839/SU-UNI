

pitagoreanTriplets = [(x,y,z) | z <- [2..],
                                x <- [1..z],
                                y <- [x..z],
                                x^2 + y^2 == z^2,
                                gcd x y == 1]

filterPairs p xs ys = [((xs !! x),(ys !! y - x)) | y <- [0..],
                                                x <- [0..y],
                                                p (xs !! x) (ys !! y - x)]

taylorElem n x = x^n / fromIntegral (product [1..n])

taylorSeries x = map (`taylorElem` x) [0..]

neper x = sum (take 50 (taylorSeries x))

streamZipWith op _ [] = []
streamZipWith op [] _ = []
streamZipWith op l1 l2 = [op (head l1) (head l2)] ++ streamZipWith op (tail l1) (tail l2) 


timesCompose f 1 = f
timesCompose f n = f . timesCompose f (n - 1)

composeF f = composes f 1
    where composes f n = timesCompose f n : composes f (succ n)

{-
main :: IO ()
main = do
    putStrLn "Enter numbers:"
    numbers <- getLine
    putStrLn ("There are " ++ show (length (words numbers)) ++ " numbers.")
-}

repeatAt str = str ++ repeatAt str


main :: IO ()
main = do
    putStrLn "Enter string:"
    str <- getLine
    putStrLn "Enter number of times to repeat:"
    num <- getLine

    let number = read num :: Int

    putStrLn (take (number * length str) (repeatAt str))

