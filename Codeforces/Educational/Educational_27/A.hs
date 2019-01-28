
import Data.List

read_strings = do
  line <- getLine
  return (words $ line)

read_ints = do
  l <- read_strings
  return (map read l :: [Int])

main = do
  n <- readLn
  arr' <- read_ints

  let arr = sort arr'
  if (arr !! n) == (arr !! (n - 1))
    then putStr("NO")
    else putStr("YES")
    
