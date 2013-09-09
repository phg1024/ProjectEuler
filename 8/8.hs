import Data.Char (digitToInt)
import Data.List (tails)

main = do str <- readFile "in.txt"
          let number = map digitToInt (concat $ lines str)
          print $ maximum $ map ( product . take 5) (tails number)
