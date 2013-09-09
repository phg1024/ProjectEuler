primes = 2 : filter isPrime [3, 5 ..]
    where
        isPrime n = n > 1 && 
                    foldr (\p r -> p*p > n || ((n `rem` p) /= 0 && r))
                    True primes

factors n = factor n primes
    where
        factor n (p:ps)
            | p * p > n         = [n]
            | n `mod` p == 0    = p : factor (n `div` p) (p:ps)
            | otherwise         = factor n ps

main = print (last (factors 600851475143)) 
