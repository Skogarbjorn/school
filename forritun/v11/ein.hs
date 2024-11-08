-- Notkun: listAll i n f
-- Fyrir:  i og n eru gildi af tagi af klasa Enum,
--         i <= n+1 og f er fall sem tekur inn eitt
--         viðfang af sama tagi.
-- Gildi:  Listinn [f(i),f(i+1),...,f(n)].
listAll i n f = map f [i..n]


-- Notkun: powerList i j
-- Fyrir:  i og j eru heiltölur.
-- Gildi:  Listi allra mögulegra lista sem eru
--         undirlistar listans [i,i+1,...,j].
powerList i j
    | i > j     = [[]]
    | otherwise = powerList (i+1) j ++ (map (i:) $ powerList (i+1) j)


main = do
    print $ powerList 2 4
    print $ powerList 5 4






