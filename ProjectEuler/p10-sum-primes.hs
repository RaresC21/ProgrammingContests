-- Find the sum of all the primes below two million.

primes = 2 : [x | x <- [3..2000000], is_prime x]
is_prime x = all (\p -> x `mod` p > 0) (try x)
  where
    try x = takeWhile (\p -> p*p <= x) primes

main = print(sum primes)
