s = [x | a<-[1..333], b<-[a+1..1000-a*2-1], let c = 1000 - a - b, a * a + b * b == c * c, a + b + c == 1000, let x = a * b * c]

main = print s
