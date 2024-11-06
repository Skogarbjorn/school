import Control.Monad

condMap4 p f x = do {
    let gamer []     = []
        gamer (x:xs) = if p x then (f x) : gamer xs else gamer xs
    in gamer x
}

condMap5 p f x = x >>= \y -> if p y then return (f y) else mzero
condMap9 p f x = foldr (\a b -> if p a then f a:b else b) [] x
condMap10 p f x = reverse (foldl (\a b -> if p b then f b:a else a) [] x)


main = do
  print (condMap5 odd (^2) [1..10])
