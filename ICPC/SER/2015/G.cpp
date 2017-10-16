#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL INF = 1000000000009;
const int MAX = 10000007;

LL event[MAX];

int main() {

    int total, success, fail; cin >> total >> success >> fail;
    for (int i = 1; i <= total; i++) {
        if (i - success >= 0)
            event[i] += event[i - success];
        if (i - fail >= 0)
            event[i] += event[i - fail];
        event[i]++;
        if (event[i] > INF) event[i] = INF;
    }

    LL amnt = event[total]+1;

    double a = 225.0 / amnt;
    double b = 200.0 / (amnt - 1);
    cout << fixed << setprecision(9) << min(a, b) << "\n";

    return 0;
}