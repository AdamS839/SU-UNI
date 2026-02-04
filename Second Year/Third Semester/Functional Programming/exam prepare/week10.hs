
pitagoreanTripples = [(a,b,c) | c <- [1..],
                                b <- [1..c],
                                a <- [1..b],
                                gcd a b == 1,
                                a^2 + b^2 == c^2]


pairs3 = [ (x, z - x) | z <- [0..], x <- [0..z] ]
-- filterTupels p xs ys = [ (xs !! fst pair, ys !! snd pair ) | pair <- pairs3, 
--                                                              p (xs !! fst pair) ( ys !! snd pair) ]

filterTupels p xs ys = [(xs !! i, ys !! j) | h <- [0..],
                                             i <- [0..h],
                                             let j = h - i,
                                             p (xs !! i) (ys !! j) ]

taylorElem n x = x^n / fromIntegral (product [1..n])

taylorSeries x = map (`taylorElem` x) [0..]

expTaylor x = sum (take 30 (taylorSeries x))


streamZipWith f (x:xs) (y:ys) = f x y : streamZipWith f xs ys

composeF f x = f x : composeF f (f x)

