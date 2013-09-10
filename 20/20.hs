import Data.Char

fac n 
    | n == 0        = 1
    | otherwise     = n * fac(n-1)

main = print (sum $ map digitToInt (show(fac 100)))
