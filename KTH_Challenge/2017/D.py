
n = int(input())
while (True) :
    if ((n * (n + 1) + (n * (n - 1)) / 2) % 4 == 0) :
        print n
        break
    n = n + 1
