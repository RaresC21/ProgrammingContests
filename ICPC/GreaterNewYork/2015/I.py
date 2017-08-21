
def update(val) :
    str_val = str(val)
    str_val = str_val[::-1]

    val = val + (int)(str_val)
    val = str(val)
    val = ''.join(sorted(val))
    return int(val)

def is_creeper(val):
    val = str(val)
    if val == "1233334444":
        return True
    if val[-3:] == "444" and val[:4] == "1233":
        for i in range(4, len(val) - 3) :
            if val[i] != '3':
                return False
        return True
    elif val[-4:] == "7777" and val[:4] == "5566":
        for i in range(4, len(val) - 4) :
            if val[i] != '6' :
                return False
        return True
    else :
        return False

T = int(input())
while T:

    met = {}
    t, M, val = map(int, raw_input().split())
    met[val] = 1
    done = False

    if is_creeper(val) :
        print t, 'C', 1
        T = T - 1
        continue
    
    for i in range(1, M) :
        val = update(val)
        if is_creeper(val) :
            print t, 'C', i + 1
            done = True
            break
        
        if (val in met) :
            print t, 'R', i + 1
            done = True
            break

        met[val] = i + 1

    if  not done:
        print t, val
    
    T = T - 1
