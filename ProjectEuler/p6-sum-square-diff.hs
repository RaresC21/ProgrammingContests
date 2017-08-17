{-
Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
-}

square :: Integer -> Integer
square x = x * x

sum_of_consecutive_nums :: Integer -> Integer
sum_of_consecutive_nums a = quot (a * (a + 1))  2

sum_of_consecutive_squares :: Integer -> Integer
sum_of_consecutive_squares a = quot (a * (a + 1) * (2 * a + 1)) 6 

diff_sums a = square (sum_of_consecutive_nums a) - (sum_of_consecutive_squares a)

main = print(diff_sums 100)
