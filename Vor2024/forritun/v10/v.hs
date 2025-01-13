import Data.Char

-- Notkun: hopverk1 x
-- Fyrir:  x er listi [x1,x2,...,xN] af hvaða
--         tagi sem er, x != [].
-- Gildi:  Listinn [[xN],...,[x2],[x1]].
hopverk1 x = foldl (\a b -> [b] : a) [] x

-- Notkun: hopverk2 x
-- Fyrir:  x er listi lista af fleytitölum.
-- Gildi:  Fleytitala sem er margfeldi allra 
--         summa gilda innri lista x.

-- Notkun: listAll i n f
-- Fyrir:  i og n eru gildi af tagi af klasa Enum, 
--         f er fall sem tekur inn eitt viðfang
--         af sama tagi.
-- Gildi:  Listinn [f(i),f(i+1),...,f(n)].
listAll i n f = map f [i..n]

-- Notkun: powerList n
-- Fyrir:  n er heiltala n >= 0.
-- Gildi:  Listi allra mögulegra lista sem eru
--         undirlistar listans [1,2,...,n].
--         Fjöldi staka er þá 2^n.
powerList n
    | n == 0    = [[]]
    | otherwise = let pl = powerList (n-1)
                  in pl ++ map (++[n]) pl

hopverk2 x = foldl (*) 1.0 (map (foldl (+) 0.0) x)

main = do
    print $ hopverk2 [[1.0,1.5],[2.5]]
    print $ hopverk2 [[],[]]
    print $ hopverk2 ([] :: [[Float]])






