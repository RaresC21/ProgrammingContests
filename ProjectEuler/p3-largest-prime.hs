{-
The prime factors of 13195 are 5, 7, 13 and 29.
What is the largest prime factor of the number 600851475143 ?
-}

input = 600851475143
  
factor :: Int -> Int -> [Int] -> Int
factor value num primes
  | (value == num)        = num
  | is_prime num primes   = if value `mod` num == 0 
                            then factor (remove_factor value num) (num + 1) (num:primes)
                            else factor (value) (num + 1) (num:primes)
  | otherwise             = factor (value) (num + 1) (primes)

remove_factor :: Int -> Int -> Int
remove_factor value num =
  if value `mod` num == 0
  then remove_factor (quot value num) (num)
  else value

is_prime x primes = all (\p -> x `mod` p > 0) (try x)
  where 
    try x = takeWhile (\p -> p*p <= x) primes

main = print (factor input 2 [])
