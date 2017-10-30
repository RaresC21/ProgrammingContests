#include "bits/stdc++.h"
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
#define A first
#define B second

const LL INF = 10000000000000009;
int N;
VI val;

int main() {
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        cin >> N;
        val.resize(N+1);
        FOR(i,1,N+1) {
            cin >> val[i];
        }
        FOR(i,1,N+1) {
            dp_max[i][0] = val[i];
        }

        LL max1 = 0, max2 = 0;
        FOR(i,1,N+1) {
            LL cur1 = max1 + val[i];
            dp_max[i][0] = cur1;
            if (cur1 < 0) max1 = 0;

            LL cur2 = max2 - val[i];
        }
    }

    return 0;
}