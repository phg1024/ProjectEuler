import System.Environment

isMod35 x = x `mod` 3 == 0 || x `mod` 5 == 0

main = print (foldl (+) 0 (filter isMod35 [1..999]))
