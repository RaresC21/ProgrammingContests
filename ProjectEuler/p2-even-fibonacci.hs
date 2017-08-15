
fibo a b = a : fibo b (a + b)
fibo_list = fibo  0 1

under_4million = takeWhile(< 4000000) fibo_list
even_fibo = filter(\x -> x `mod` 2 == 0) under_4million

main = print (sum even_fibo)
