factorize n (p:ps)
        | n `rem` p == 0    = p : (factorize n ps)
        | otherwise         = factorize n ps

factorize n [] = []

d n = sum(factorize n [1..n-1])

main = print $ sum([x | x<-[1..9999], let y = d(x), let z = d(y), y < 10000, y /= x, z == x])
