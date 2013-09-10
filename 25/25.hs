fibs = 1 : 1 : zipWith (+) fibs (tail fibs)

main = print ( head [x | y<-(zip [1..] fibs), let x = fst y, length(show(snd y))==1000] )
