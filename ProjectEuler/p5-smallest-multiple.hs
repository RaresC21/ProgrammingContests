{-
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
-}

gcd' :: Integer -> Integer -> Integer
gcd' a 0 = a
gcd' 0 b = b
gcd' a b = gcd (b `mod` a) (a)

lcm' a b = quot (a * b) (gcd' a b)

range_lcm l r = foldl (\a b -> lcm a b) 1 [l..r]

main = print (range_lcm 1 20)
