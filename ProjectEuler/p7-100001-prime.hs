-- What is the 10 001st prime number?

primes = 2 : [x | x <- [3..], is_prime x]
is_prime x = all (\p -> x `mod` p > 0) (try x)
  where
    try x = takeWhile (\p -> p*p <= x) primes

main = print(primes !! 10000)
