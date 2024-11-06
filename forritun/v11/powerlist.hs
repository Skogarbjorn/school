-- Notkun: powerList i j
-- Fyrir:  i og j eru af sama tagi sem
--         tilheyrir tagaklösunum Enum og Ord
-- Gildi:  Listi allra mögulegra lista sem eru
--         undirlistar listans [i,i+1,...,j].
powerList :: (Enum a, Ord a) => a -> a -> [[a]]
powerList i j
    | i > j     = [[]]
    | otherwise = powerList (succ i) j ++ (map (i:) $ powerList (succ i) j)

main = do
    print $ powerList 2 4
