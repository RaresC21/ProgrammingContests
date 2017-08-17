{-
There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
-}

solve = [a*b*c | a <- [1..999], b <- [1..(1000 - a)], let c = 1000 - a - b, is_triple a b c ]
  where
    is_triple a b c = a*a + b*b == c*c
    
main = print (solve)
