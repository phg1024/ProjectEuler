main = print ( sum([1..100])*sum([1..100]) - (sum [x | y<-[1..100], let x = y * y]) )
