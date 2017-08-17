{-
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
Find the largest palindrome made from the product of two 3-digit numbers.
-}

is_palindrome :: String -> Bool
is_palindrome [] = True
is_palindrome [_] = True
is_palindrome string = ((head string) == (last string)) && is_palindrome (init (tail string))

prods = [p | x <- [100..999], y <- [100..999], let p = x * y, is_palindrome(show p)]

main = print(maximum prods)
