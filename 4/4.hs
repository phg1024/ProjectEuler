isPalindrome x = s == reverse s
    where s = show x

main = print ( maximum (filter isPalindrome [x | y<-[100..999], z<-[y..999], let x=y*z] ) )
