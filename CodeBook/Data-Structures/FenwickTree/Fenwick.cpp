#include <bits/stdc++.h>
using namespace std;

const int MAX = 100005;

class Fenwick {
private:
    int BIT[MAX];
    int N;
    
public:
    Fenwick(int N) : N(N) {
        memset(BIT, 0, sizeof(BIT));
    }

    void update(int x, int val) {
        for (; x <= N; x += x & -x)
            BIT[x] += val;
    }

    int query(int x) {
        int sum = 0;
        for (; x > 0; x -= x & -x)
            sum += BIT[x];
        return sum;
    }
};